#include <nwl_pch.hpp>
#include "data_image.h"

#include <io/io_exception.h>

namespace NWL
{
	ImageInfo::ImageInfo(Int32 nX, Int32 nY, UInt8 nCh) :
		nWidth(nX), nHeight(nY), nChannels(nCh),
		pxlFormat(PXF_R8G8B8A8_UINT32) { }
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
		return rStream;
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
	}

	std::ostream& operator<<(std::ostream& rStream, const ImageInfo& rInfo) { return rInfo.operator<<(rStream); }
	std::istream& operator>>(std::istream& rStream, ImageInfo& rInfo) { return rInfo.operator>>(rStream); }
}
namespace NWL
{
	Image::Image() : AMemUser(), m_Info(ImageInfo()), m_pData(nullptr) { }
	Image::Image(const ImageInfo& rInfo, UByte* pData) : m_Info(rInfo), m_pData(pData) {}
	Image::Image(const Image& rCpy) : m_Info(rCpy.m_Info) { SetData(rCpy.m_pData, rCpy.m_Info); }
	Image::~Image() { if (m_pData != nullptr) { MemSys::DelTArr<UByte>(m_pData, GetSize()); } }
	// --setters
	void Image::SetData(UByte* pData, Size nW, Size nH, Size nCh) {
		if (pData == nullptr) { if (m_pData != nullptr) { MemSys::DelTArr<UByte>(m_pData, GetSize()); } }
		m_Info.nWidth = nW;
		m_Info.nHeight = nH;
		m_Info.nChannels = nCh;
		m_pData = MemSys::NewTArr<UByte>(GetSize());
		memcpy(pData, m_pData, GetSize());
	}
	void Image::SetData(UByte* pData, const ImageInfo& rInfo) {
		if (m_pData != nullptr) { MemSys::DelTArr<UByte>(m_pData, GetSize()); }
		m_Info.nWidth = rInfo.nWidth;
		m_Info.nHeight = rInfo.nHeight;
		m_Info.nChannels = rInfo.nChannels;
		m_pData = MemSys::NewTArr<UByte>(GetSize());
		if (pData == nullptr) { return; }
		memcpy(pData, m_pData, GetSize());
	}
	void Image::SetPixel(Int32 nX, Int32 nY, UByte nR, UByte nG, UByte nB) {
		Size szCoord = NWL_XY_TO_X(nX * m_Info.nChannels, nY * m_Info.nChannels, m_Info.nWidth);
		const Size szData = GetSize();
		if (szCoord >= szData) { throw Exception("outside of image bounds", ERC_DATA_OVERFLOW); }
		m_pData[szCoord++ % szData] = nR;
		m_pData[szCoord++ % szData] = nG;
		m_pData[szCoord++ % szData] = nB;
	}
	void Image::SetPixel(Int32 nX, Int32 nY, UByte nR, UByte nG, UByte nB, UByte nA) {
		Size szCoord = NWL_XY_TO_X(nX * m_Info.nChannels, nY * m_Info.nChannels, m_Info.nWidth);
		const Size szData = GetSize();
		if (szCoord >= szData) { throw Exception("outside of image bounds", ERC_DATA_OVERFLOW); }
		m_pData[szCoord++ % szData] = nR;
		m_pData[szCoord++ % szData] = nG;
		m_pData[szCoord++ % szData] = nB;
		m_pData[szCoord++ % szData] = nA;
	}
	void Image::SetPixel(Int32 nX, Int32 nY, UInt32 nColor) {
		Size szCoord = NWL_XY_TO_X(nX * m_Info.nChannels, nY * m_Info.nChannels, m_Info.nWidth);
		const Size szData = GetSize();
		if (szCoord >= szData) { throw Exception("outside of image bounds", ERC_DATA_OVERFLOW); }
		memcpy(&m_pData[szCoord % szData], &nColor, static_cast<Size>(m_Info.nChannels % 4));
	}
	// --operators
	void Image::operator=(const Image& rImg) { SetData(rImg.m_pData, rImg.m_Info); }
}