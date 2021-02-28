#include <nwl_pch.hpp>
#include "data_image.h"
#include <io/io_exception.h>

namespace NWL
{
	// --setters
	void ImageInfo::SetPixel(UInt32 nX, UInt32 nY, Pixel pxlColor) {
		pxlData[NWL_XY_TO_X(nX, nY, nWidth) % GetDataSize()] = pxlColor;
	}
	void ImageInfo::SetPixels(UByte* pData) {
		if (pData == nullptr) { pxlData.clear(); return; }
		else { pxlData.resize(GetDataSize()); memcpy(&pxlData[0], pData, GetDataSize()); }
	}
	// --operators
	ImageInfo& ImageInfo::operator=(const ImageBmpInfo& rInfo) {
		nWidth = rInfo.nWidth;
		nHeight = rInfo.nHeight;
		nChannels = rInfo.nChannels;
		pxlFormat = rInfo.pxlFormat;
		pxlData = rInfo.pxlData;
		return *this;
	}
	ImageInfo& ImageInfo::operator=(const ImagePngInfo& rInfo) {
		nWidth = rInfo.nWidth;
		nHeight = rInfo.nHeight;
		nChannels = rInfo.nChannels;
		pxlFormat = rInfo.pxlFormat;
		pxlData = rInfo.pxlData;
		return *this;
	}
	ImageInfo& ImageInfo::operator=(const ImageInfo& rInfo) {
		nWidth = rInfo.nWidth;
		nHeight = rInfo.nHeight;
		nChannels = rInfo.nChannels;
		pxlFormat = rInfo.pxlFormat;
		pxlData = rInfo.pxlData;
		return *this;
	}
	std::ostream& ImageInfo::operator<<(std::ostream& rStream) const {
		return rStream <<
			"--==<image_info>==--" << std::endl <<
			"width:" << nWidth << std::endl <<
			"height:" << nHeight << std::endl <<
			"channels:" << nChannels << std::endl <<
			"pixel_format:" << pxlFormat << std::endl <<
			"--==</image_info>==--" << std::endl;
	}
	std::istream& ImageInfo::operator>>(std::istream& rStream) {
		Char strBuf[256]{ 0 };
		UInt32 unPxlFormat;
		rStream.getline(strBuf, 256, ':');
		rStream >> nWidth; rStream.get();
		rStream.getline(strBuf, 256, ':');
		rStream >> nHeight; rStream.get();
		rStream.getline(strBuf, 256, ':');
		rStream >> nChannels; rStream.get();
		rStream.getline(strBuf, 256, ':');
		rStream >> unPxlFormat; rStream.get();
		pxlFormat = static_cast<PixelFormats>(unPxlFormat);
		return rStream;
	}
}
namespace NWL
{
	// --operators
	std::ostream& ImageBmpInfo::operator<<(std::ostream& rStream) const {
		ImageInfo::operator<<(rStream);
		return rStream <<
			"--==<image_bmp_info>==--" << std::endl <<
			"--==</image_bmp_info>==--" << std::endl;
	}
	std::istream& ImageBmpInfo::operator>>(std::istream& rStream) {
		rStream.read(reinterpret_cast<Byte*>(&File), sizeof(File));
		rStream.read(reinterpret_cast<Byte*>(&Desc), sizeof(Desc));
		if (Desc.nPxBits != 8 && Desc.nPxBits != 24 && Desc.nPxBits != 32) { throw Exception("unsupported format"); }
		if (Desc.szCompression == BI_BITFIELDS) { rStream.read(reinterpret_cast<Byte*>(&Clut), sizeof(UInt32) * 4); }
		rStream.seekg(File.szOffset, rStream.beg);

		nWidth = std::abs(Desc.nWidth);
		nHeight = std::abs(Desc.nHeight);
		nChannels = Desc.nPxBits / 8;
		pxlFormat = PxfGet(nChannels);
		pxlData.resize(GetPxlCount());

		DArray<UByte> pxlBuf;
		pxlBuf.resize(Desc.szImage);
		rStream.read(reinterpret_cast<Byte*>(&pxlBuf[0]), pxlBuf.size());
		if (nChannels == 1) {	// indexed bitmap;
			nChannels = 4;
			pxlFormat = PxfGet(nChannels);
			// pxlBuf contains indices; we need to load our colors there;
			DArray<UByte> clrIndices(std::move(pxlBuf));
			DArray<Pixel> clrPalette((Desc.nClrUsed), Pixel(0));
			pxlBuf.resize(clrIndices.size() * 4);
			// our rgba palette is allocated after file header, dbi header and optional color masks
			rStream.seekg(-static_cast<Int32>((clrPalette.size() * nChannels) + clrIndices.size()), rStream.cur);
			rStream.read(reinterpret_cast<Byte*>(&clrPalette[0]), clrPalette.size() * nChannels);
			// write all colors from palette into the buffer via indices
			for (Int32 n = 0; n != pxlData.size(); n += 1) { pxlData[n] = clrPalette[clrIndices[n]]; }
		}
		else {	// simple rgb/rgba
			Int32 nPad = ((nWidth * nChannels) % 4) % 4;
			Int32 nBegX, nBegY;
			Int32 nEndX, nEndY;
			Int32 nDirX, nDirY;
			// sometimes bmp format uses negative height
			if (Desc.nHeight < 0) {
				nBegY = nHeight - 1;
				nEndY = -1;
				nDirY = -1;
			}
			else {
				nBegY = 0;
				nEndY = +nHeight;
				nDirY = +1;
			}
			// maybe bmp format uses negative width
			if (Desc.nWidth < 0) {
				nBegX = nWidth - 1;
				nEndX = -1;
				nDirX = -1;
			}
			else {
				nBegX = 0;
				nEndX = +nWidth;
				nDirX = +1;
			}
			Int32 nBufGet = 0;
			for (Int32 iy = nBegY; iy != nEndY; iy += nDirY) {
				Int32 nOffsetY = iy * nWidth;
				for (Int32 ix = nBegX; ix != nEndX; ix += nDirX) {
					for (Int8 i = 0; i < nChannels; i++) {
						pxlData[nOffsetY + ix][i] = pxlBuf[nBufGet++];
					}
				}
				nBufGet += nPad;
			}
		}
		return rStream;
	}

}
namespace NWL
{
	// --operators
	std::ostream& ImagePngInfo::operator<<(std::ostream& rStream) const {
		ImageInfo::operator<<(rStream);
		return rStream <<
			"--==<image_png_info>==--" << std::endl <<
			"--==</image_png_info>==--" << std::endl;
	}
	std::istream& ImagePngInfo::operator>>(std::istream& rStream) {
		Char strBuf[256]{ 0 };
		UInt32 unPxlFormat;
		rStream.getline(strBuf, 256, ':');
		rStream >> nWidth; rStream.get();
		rStream.getline(strBuf, 256, ':');
		rStream >> nHeight; rStream.get();
		rStream.getline(strBuf, 256, ':');
		rStream >> nChannels; rStream.get();
		rStream.getline(strBuf, 256, ':');
		rStream >> unPxlFormat; rStream.get();
		pxlFormat = static_cast<PixelFormats>(unPxlFormat);
		return rStream;
	}

}