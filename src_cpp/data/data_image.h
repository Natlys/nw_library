#ifndef NWL_DATA_IMAGE_H
#define NWL_DATA_IMAGE_H
#include <nwl_core.hpp>
#include <core/nwl_info.h>
#include <core/nwl_container.h>
#include <core/nwl_switch.h>
#include <memory/mem_sys.h>
namespace NWL
{
	struct Pixel;
	struct ImageInfo;
	struct ImageBmpInfo;
	struct ImagePngInfo;
}
namespace NWL
{
	/// Pixel struct
	struct NWL_API Pixel
	{
	public:
		union {
			unsigned int rgbaVal;
			struct { UByte r, g, b, a; };
			UByte rgba[4]{ 0 };
		};
	public:
		Pixel() = default;
		Pixel(UInt32 nValue) : rgbaVal(nValue) { }
		Pixel(UByte red, UByte green, UByte blue, UByte alpha) :
			rgba{ red, green, blue, alpha } { }
		// --operators
		inline UByte& operator[](UInt8 nIdx) { return rgba[nIdx]; }
		inline const UByte& operator[](UInt8 nIdx) const { return rgba[nIdx]; }
		inline void operator=(UInt32 nValue) { rgbaVal = nValue; }
		inline void operator=(const Pixel& rCpy) { rgbaVal = rCpy.rgbaVal; }
	};
}
namespace NWL
{
	/// ImageInfo struct
	struct NWL_API ImageInfo : public AInfo
	{
	public:
		PixelFormats pxlFormat = PXF_R8G8B8A8_UINT32;
		Int32 nWidth = 1;
		Int32 nHeight = 1;
		Int32 nChannels = 4;
		DArray<Pixel> pxlData = { Pixel(255u, 255u, 255u, 255u) };
	public:
		// --getters
		inline Size GetDataSize() const { return static_cast<Size>(abs(nChannels) * abs(nWidth) * abs(nHeight)); }
		inline UInt64 GetPxlCount() const { return static_cast<UInt64>(abs(nWidth) * abs(nHeight)); }
		inline Pixel GetPixel(UInt32 nX, UInt32 nY) { return pxlData[NWL_XY_TO_X(nX, nY, nWidth) % GetDataSize()]; }
		// --setters
		void SetPixel(UInt32 szX, UInt32 nY, Pixel pxlColor);
		void SetPixels(UByte* pData);
		// --operators
		ImageInfo& operator=(const ImageBmpInfo& rInfo);
		ImageInfo& operator=(const ImagePngInfo& rInfo);
		ImageInfo& operator=(const ImageInfo& rInfo);
		virtual std::ostream& operator<<(std::ostream& rStream) const override;
		virtual std::istream& operator>>(std::istream& rStream) override;
	};
}
namespace NWL
{
	/// ImageBmpInfo struct
	/// Description:
	/// --used for loading of .bmp formatted files
	/// Interface:
	/// ->load a bitmap as binary file->read headers "file" and "data"
	/// ->if the image is indexed - load color pallete
	/// ->read pixel data with offset which is defined in "file" header
	/// ->in the case of 24bit and not multiple-of-4 sizes, we need to consider padding
	struct NWL_API ImageBmpInfo : public ImageInfo
	{
	public:
#pragma pack(push, 1) // add padding 16->14
		struct {
			UInt16 nType = 0x4d; // two encoded letters;usually "bm"
			UInt32 szData = 3; // size of the file in bytes
			UInt16 nReserved1 = 0; // it is reserved, (can be used by a programmer)
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
		} Clut;	// color lookup table
#pragma pack(pop)
	public:
		// --operators
		virtual std::ostream& operator<<(std::ostream& rStream) const override;
		virtual std::istream& operator>>(std::istream& rStream) override;
	};
	/// ImagePngInfo struct
}
namespace NWL
{
	struct NWL_API ImagePngInfo : public ImageInfo
	{
	public:
		// --operators
		virtual std::ostream& operator<<(std::ostream& rStream) const override;
		virtual std::istream& operator>>(std::istream& rStream) override;
	};
}
#endif	// NWL_DATA_IMAGE_H