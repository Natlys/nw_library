#ifndef NW_IO_STREAM_H
#define NW_IO_STREAM_H
#include <nwl_core.hpp>
namespace NW
{
	using in_stream = std::istream;
	using out_stream = std::ostream;
	using io_stream = std::iostream;
	using in_stream_file = std::ifstream;
	using out_stream_file = std::ofstream;
	using io_stream_file = std::fstream;
}
#endif	// NW_IO_STREAM_H