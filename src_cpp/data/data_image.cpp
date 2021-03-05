#include <nwl_pch.hpp>
#include "data_image.h"
#include <io/io_error.h>
namespace NWL
{
	// --setters
	void image_info::set_pixel(ui32 x, ui32 y, pixel pxl) {
		pxl_data[NWL_XY_TO_X(x, y, size_x) % get_size()] = pxl;
	}
	void image_info::set_pixels(ubyte* data_ptr) {
		if (data_ptr == nullptr) {
			pxl_data.clear(); return;
		}
		else {
			pxl_data.resize(get_size());
			memcpy(&pxl_data[0], data_ptr, get_size());
		}
	}
	// --operators
	image_info& image_info::operator=(const image_bmp_info& rInfo) {
		size_x = rInfo.size_x;
		size_y = rInfo.size_y;
		nof_channels = rInfo.nof_channels;
		pxl_format = rInfo.pxl_format;
		pxl_data = rInfo.pxl_data;
		return *this;
	}
	image_info& image_info::operator=(const image_png_info& rInfo) {
		size_x = rInfo.size_x;
		size_y = rInfo.size_y;
		nof_channels = rInfo.nof_channels;
		pxl_format = rInfo.pxl_format;
		pxl_data = rInfo.pxl_data;
		return *this;
	}
	image_info& image_info::operator=(const image_info& rInfo) {
		size_x = rInfo.size_x;
		size_y = rInfo.size_y;
		nof_channels = rInfo.nof_channels;
		pxl_format = rInfo.pxl_format;
		pxl_data = rInfo.pxl_data;
		return *this;
	}
	std::ostream& image_info::operator<<(std::ostream& stm) const {
		return stm <<
			"--==<image_info>==--" << std::endl <<
			"size_x:" << size_x << std::endl <<
			"size_y:" << size_y << std::endl <<
			"channels:" << nof_channels << std::endl <<
			"pixel_format:" << pxl_format << std::endl <<
			"--==</image_info>==--" << std::endl;
	}
	std::istream& image_info::operator>>(std::istream& stm) {
		sbyte str_buf[256]{ 0 };
		ui32 pxl_format_num = 0;
		stm.getline(str_buf, 256, ':');
		stm >> size_x; stm.get();
		stm.getline(str_buf, 256, ':');
		stm >> size_y; stm.get();
		stm.getline(str_buf, 256, ':');
		stm >> nof_channels; stm.get();
		stm.getline(str_buf, 256, ':');
		stm >> pxl_format_num; stm.get();
		pxl_format = static_cast<pixel_formats>(pxl_format_num);
		return stm;
	}
}
namespace NWL
{
	// --operators
	std::ostream& image_bmp_info::operator<<(std::ostream& stm) const {
		image_info::operator<<(stm);
		return stm <<
			"--==<image_bmp_info>==--" << std::endl <<
			"--==</image_bmp_info>==--" << std::endl;
	}
	std::istream& image_bmp_info::operator>>(std::istream& stm) {
		stm.read(reinterpret_cast<sbyte*>(&file_info), sizeof(file_info));
		stm.read(reinterpret_cast<sbyte*>(&data_info), sizeof(data_info));
		if (data_info.nof_pixel_bits != 8 && data_info.nof_pixel_bits != 24 && data_info.nof_pixel_bits != 32) { throw error("unsupported format"); }
		stm.seekg(file_info.data_offset, stm.beg);

		size_x = std::abs(data_info.width);
		size_y = std::abs(data_info.height);
		nof_channels = data_info.nof_pixel_bits / 8;
		pxl_format = pxf_get(nof_channels);
		pxl_data.resize(get_count());

		darray<ubyte> pxl_buf;
		pxl_buf.resize(data_info.image_size);
		stm.read(reinterpret_cast<sbyte*>(&pxl_buf[0]), pxl_buf.size());
		if (nof_channels == 1) {	// indexed bitmap;
			nof_channels = 4;
			pxl_format = pxf_get(nof_channels);
			// pxl_buf contains indices; we need to load our colors there;
			darray<ubyte> indices(std::move(pxl_buf));
			darray<pixel> colors((data_info.clrs_used), pixel(0));
			pxl_buf.resize(indices.size() * 4);
			// our rgba palette is allocated after file header, dbi header and optional color masks
			stm.seekg(-static_cast<si32>((colors.size() * nof_channels) + indices.size()), stm.cur);
			stm.read(reinterpret_cast<sbyte*>(&colors[0]), colors.size() * nof_channels);
			// write all colors from palette into the buffer via indices
			for (si32 n = 0; n != pxl_data.size(); n += 1) { pxl_data[n] = colors[indices[n]]; }
		}
		else {	// simple rgb/rgba
			si32 nPad = ((size_x * nof_channels) % 4) % 4;
			si32 nBegX, nBegY;
			si32 nEndX, nEndY;
			si32 nDirX, nDirY;
			// sometimes bmp format uses negative size_y
			if (data_info.width < 0) {
				nBegY = size_y - 1;
				nEndY = -1;
				nDirY = -1;
			}
			else {
				nBegY = 0;
				nEndY = +size_y;
				nDirY = +1;
			}
			// maybe bmp format uses negative size_x
			if (data_info.height < 0) {
				nBegX = size_x- 1;
				nEndX = -1;
				nDirX = -1;
			}
			else {
				nBegX = 0;
				nEndX = +size_x;
				nDirX = +1;
			}
			si32 nBufGet = 0;
			for (si32 iy = nBegY; iy != nEndY; iy += nDirY) {
				si32 nOffsetY = iy * size_x;
				for (si32 ix = nBegX; ix != nEndX; ix += nDirX) {
					for (si8 i = 0; i < nof_channels; i++) {
						pxl_data[nOffsetY + ix][i] = pxl_buf[nBufGet++];
					}
				}
				nBufGet += nPad;
			}
		}
		return stm;
	}

}
namespace NWL
{
	// --operators
	std::ostream& image_png_info::operator<<(std::ostream& stm) const {
		image_info::operator<<(stm);
		return stm <<
			"--==<image_png_info>==--" << std::endl <<
			"--==</image_png_info>==--" << std::endl;
	}
	std::istream& image_png_info::operator>>(std::istream& stm) {
		sbyte str_buf[256]{ 0 };
		ui32 pxl_format_num = 0;
		stm.getline(str_buf, 256, ':');
		stm >> size_x; stm.get();
		stm.getline(str_buf, 256, ':');
		stm >> size_y; stm.get();
		stm.getline(str_buf, 256, ':');
		stm >> nof_channels; stm.get();
		stm.getline(str_buf, 256, ':');
		stm >> pxl_format_num; stm.get();
		pxl_format = static_cast<pixel_formats>(pxl_format_num);
		return stm;
	}

}