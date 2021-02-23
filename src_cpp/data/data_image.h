#ifndef NWL_DATA_IMAGE_H
#define NWL_DATA_IMAGE_H

#include <nwl_core.hpp>

#include <memory/mem_sys.h>

namespace NWL
{
	/// BitMapInfo struct
	/// Description:
	/// --used for loading of .bmp formatted files
	/// Interface:
	/// ->load a bitmap as binary file->read headers "file" and "data"
	/// ->if the image is indexed - load color pallete
	/// ->read pixel data with offset which is defined in "file" header
	/// ->in the case of 24bit and not multiple-of-4 sizes, we need to consider padding
	struct NWL_API BitMapInfo
	{
#pragma pack(push, 1) // add padding 16->14
		struct {
			UInt16 nType = 0; // two encoded letters;usually "bm"
			UInt32 szData = 3; // size of the file in bytes
			UInt16 nReserved1 = 0; // it is reserved
			UInt16 nReserved2 = 0; // so it is always zero
			UInt32 szOffset = 54; // offset to the pixel data
		}File;	// file info
#pragma pack(pop)
#pragma pack(push, 1)
		struct {
			UInt32 szData = 3; // size of the header in bytes
			Int32 nWidth = 1; // bitmap width in pixels
			Int32 nHeight = 1; // bitmap height in pixels

			UInt16 nPlanes = 1; // always 1
			UInt16 nPxBits = 24; // bpp
			UInt32 szCompression = 0; // 24bpp = 0; 32bpp = 3
			UInt32 szImage = 3; // 0 for uncompressed
			Int32 nXppm = 0;
			Int32 nYppm = 0;
			UInt32 nClrUsed = 0; // indexed pallete count; zero for all available collors;
			UInt32 nClrNeed = 0; // required colors for bitmap
		}Desc;	// description
#pragma pack(pop)
#pragma pack(push, 1)
		struct {
			UInt32 nRMask = 0x00'ff'00'00; // bit mask for the red channel
			UInt32 nGMask = 0x00'00'ff'00; // bit mask for the green channel
			UInt32 nBMask = 0x00'00'00'ff; // bit mask for the blue channel
			UInt32 nAMask = 0xff'00'00'00; // bit mask for the alpha channel
			UInt32 nColorSpaceType = 0x73'52'47'42; // default s'rgb
			UInt32 nUnused = 0x73'52'47'42; // unused data for s'rgb clr space
		}Clut;	// color lookup table
#pragma pack(pop)
	};
}
namespace NWL
{
	/// ImageInfo struct
	struct NWL_API ImageInfo
	{
	public:
		Int32 nWidth = 1;
		Int32 nHeight = 1;
		Int32 nChannels = 1;
		PixelFormats pxlFormat = PXF_R8G8B8A8_UINT32;
	public:
		ImageInfo(Int32 nX = 1, Int32 nY = 1, UInt8 nCh = 3);
		// --getters
		inline Size GetSize()	{ return static_cast<Size>(abs(nChannels) * abs(nWidth) * abs(nHeight)); }
		// --operators
		std::ostream& operator<<(std::ostream& rStream) const;
		std::istream& operator>>(std::istream& rStream);
	};
	std::ostream& operator<<(std::ostream& rStream, const ImageInfo& rInfo);
	std::istream& operator>>(std::istream& rStream, ImageInfo& rInfo);
}
namespace NWL
{
	class NWL_API Image : public AMemUser
	{
	public:
		Image();
		Image(const ImageInfo& rInfo, UByte* pData);
		Image(const Image& rImg);
		virtual ~Image();
		// --getters
		inline UByte* GetData()					{ return m_pData; }
		inline Size GetSize() const				{ return static_cast<Size>(abs(m_Info.nChannels) * abs(m_Info.nWidth) * abs(m_Info.nHeight)); }
		inline Int32 GetSizeW() const			{ return m_Info.nWidth; }
		inline Int32 GetSizeH() const			{ return m_Info.nHeight; }
		inline Int32 GetChannels() const		{ return m_Info.nChannels; }
		inline PixelFormats GetFormat() const	{ return m_Info.pxlFormat; }
		inline const ImageInfo& GetInfo() const	{ return m_Info; }
		// --setters
		void SetData(UByte* pData, Size nW, Size nH, Size nCh);
		void SetData(UByte* pData, const ImageInfo& rInfo);
		void SetPixel(Int32 nX, Int32 nY, UByte nR, UByte nG, UByte nB);
		void SetPixel(Int32 nX, Int32 nY, UByte nR, UByte nG, UByte nB, UByte nA);
		void SetPixel(Int32 nX, Int32 nY, UInt32 unColor);
		// --operators
		void operator=(const Image& rImg);
	private:
		ImageInfo m_Info;
		UByte* m_pData;
	};
}

#endif	// NWL_DATA_IMAGE_H