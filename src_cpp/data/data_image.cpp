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
	std::ostream& operator<<(std::ostream& rStream, const ImageInfo& rInfo) { return rInfo.operator<<(rStream); }
	std::istream& operator>>(std::istream& rStream, ImageInfo& rInfo) { return rInfo.operator>>(rStream); }
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
		UInt32 nInfoOffset = sizeof(File) + sizeof(Desc);
		rStream.read(reinterpret_cast<Byte*>(&File), sizeof(File));
		rStream.read(reinterpret_cast<Byte*>(&Desc), sizeof(Desc));
		if (Desc.nPxBits != 8 && Desc.nPxBits != 24 && Desc.nPxBits != 32) { throw Exception("unsupported format"); }
		if (Desc.szCompression == BI_BITFIELDS) {
			rStream.read(reinterpret_cast<Byte*>(&Clut), sizeof(UInt32) * 4);
			nInfoOffset += sizeof(Clut);
		}
		rStream.seekg(File.szOffset, rStream.beg);

		nWidth = Desc.nWidth;
		nHeight = Desc.nHeight;
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
			DArray<Pixel> clrPalette((File.szOffset - nInfoOffset) / nChannels, Byte());
			pxlBuf.resize(clrIndices.size() * 4);
			// our rgba palette is allocated after file header, dbi header and optional color masks
			rStream.seekg(nInfoOffset, rStream.beg);
			rStream.read(reinterpret_cast<Byte*>(&clrPalette[0]), clrPalette.size() * nChannels);
			// write all colors from palette into the buffer via indices
			for (Int32 n = 0; n != pxlData.size(); n += 1) {
				for (Int8 i = 0; i < nChannels; i += 1) {
					pxlBuf[(n * nChannels) + i] = clrPalette[clrIndices[n]][i];
				}
			}
		}
		
		memcpy(&pxlData[0], &pxlBuf[0], pxlBuf.size());
#if false
		Int32 nPad = (4 - (nWidth * nChannels) % 4) % 4;
		Int32 nBegY = 0, nBegX = 0;
		Int32 nEndY = 0, nEndX = nWidth;
		Int32 nDirY = 0, nDirX = +1;
		if (nHeight < 0) {
			nHeight = -nHeight;
			nBegY = 0 - 0;
			nEndY = nHeight + 0;
			nDirY = +1;
		}
		else if (nHeight > 0) {
			nHeight = +nHeight;
			nBegY = nHeight - 1;
			nEndY = -1 + 0;
			nDirY = -1;
		}
		for (Int32 yi = nBegY; yi != nEndY; yi += nDirY) {
			Int32 nOffsetY = yi * nWidth;
			for (Int32 xi = nBegX; xi != nEndX; xi += nDirX) {
				pxlData[(nOffsetY + xi) / 4][xi % 4] = pxlBuf[nOffsetY + xi];
			}
		}
#endif
		return rStream;
	}

	std::ostream& operator<<(std::ostream& rStream, const ImageBmpInfo& rInfo) { return rInfo.operator<<(rStream); }
	std::istream& operator>>(std::istream& rStream, ImageBmpInfo& rInfo) { return rInfo.operator>>(rStream); }
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

	std::ostream& operator<<(std::ostream& rStream, const ImagePngInfo& rInfo) { return rInfo.operator<<(rStream); }
	std::istream& operator>>(std::istream& rStream, ImagePngInfo& rInfo) { return rInfo.operator>>(rStream); }
}