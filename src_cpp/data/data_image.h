#ifndef NWL_DATA_IMAGE_H
#define NWL_DATA_IMAGE_H
#include <nwl_core.hpp>
#include <core/nwl_info.h>
#include <core/nwl_container.h>
#include <core/nwl_switch.h>
#include <memory/mem_sys.h>
namespace NWL
{
	struct pixel;
	struct image_info;
	struct image_bmp_info;
	struct image_png_info;
}
namespace NWL
{
	/// pixel struct
	struct NWL_API pixel
	{
	public:
		union {
			ui32 rgba_num;
			struct { ubyte r, g, b, a; };
			ubyte rgba[4]{ 0 };
		};
	public:
		pixel(ui32 value = 0x00'00'00'00) : rgba_num(value) { }
		pixel(ubyte red, ubyte green, ubyte blue, ubyte alpha) :
			rgba{ red, green, blue, alpha } { }
		// --operators
		inline ubyte& operator[](ui8 idx) { return rgba[idx]; }
		inline const ubyte& operator[](ui8 idx) const { return rgba[idx]; }
		inline void operator=(ui32 value) { rgba_num = value; }
		inline void operator=(const pixel& copy) { rgba_num = copy.rgba_num; }
	};
}
namespace NWL
{
	/// image_information struct
	struct NWL_API image_info : public a_info
	{
	public:
		pixel_formats pxl_format = PXF_R8G8B8A8_UINT32;
		si32 size_x = 1;
		si32 size_y = 1;
		si32 nof_channels = 4;
		darray<pixel> pxl_data = { pixel(255u, 255u, 255u, 255u) };
	public:
		// --getters
		inline size get_size() const { return static_cast<size>(abs(nof_channels) * abs(size_x) * abs(size_y)); }
		inline ui64 get_count() const { return static_cast<ui64>(abs(size_x) * abs(size_y)); }
		inline pixel get_pixel(ui32 x, ui32 y) { return pxl_data[NWL_XY_TO_X(x, y, size_x) % get_size()]; }
		// --setters
		void set_pixel(ui32 x, ui32 y, pixel pxl);
		void set_pixels(ubyte* data_ptr);
		// --operators
		image_info& operator=(const image_bmp_info& info);
		image_info& operator=(const image_png_info& info);
		image_info& operator=(const image_info& info);
		virtual std::ostream& operator<<(std::ostream& stm) const override;
		virtual std::istream& operator>>(std::istream& stm) override;
	};
}
namespace NWL
{
	/// image_bmp_info struct
	/// description:
	/// --used for loading of .bmp formatted files
	/// interface:
	/// ->load a bitmap as binary file->read headers "file" and "data"
	/// ->if the image is indexed - load color pallete
	/// ->read pixel data with offset which is defined in "file" header
	/// ->in the case of 24bit and not multiple-of-4 sizes, we need to consider padding
	struct NWL_API image_bmp_info : public image_info
	{
	public:
#pragma pack(push, 1) // add padding 16->14
		struct {
			ui16 type_code = 0x4d;		// two encoded letters;usually "bm"
			ui32 header_size = 14;		// size of the file in bytes
			ui16 reserved1 = 0;			// it is reserved, (can be used by a programmer)
			ui16 reserved2 = 0;			// so it is always zero
			ui32 data_offset = 54;		// offset to the pixel data
		} file_info;	// file info
#pragma pack(pop)
#pragma pack(push, 1)
		struct {
			ui32 header_size = 3;	// size of the header in bytes
			si32 width = 1;			// bitmap width in pixels
			si32 height = 1;		// bitmap height in pixels
			ui16 nof_planes = 1;		// always 1
			ui16 nof_pixel_bits = 24;	// bpp
			ui32 compression_type = 0;	// 24bpp = 0; 32bpp = 3
			ui32 image_size = 0;		// 0 for uncompressed
			si32 ppm_x = 0;
			si32 ppm_y = 0;
			ui32 clrs_used = 0;	// indexed pallete count; zero for all available collors;
			ui32 clrs_need = 0;	// required colors for bitmap
		} data_info;	// description
#pragma pack(pop)
	public:
		// --operators
		virtual std::ostream& operator<<(std::ostream& stm) const override;
		virtual std::istream& operator>>(std::istream& stm) override;
	};
}
namespace NWL
{
	/// image_png_info struct
	struct NWL_API image_png_info : public image_info
	{
	public:
		// --operators
		virtual std::ostream& operator<<(std::ostream& stm) const override;
		virtual std::istream& operator>>(std::istream& stm) override;
	};
}
#endif	// NWL_DATA_IMAGE_H