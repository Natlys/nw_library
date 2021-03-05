#ifndef NWL_IO_STREAM_H
#define NWL_IO_STREAM_H
#include <nwl_core.hpp>
namespace NWL
{
	using in_stream = std::istream;
	using out_stream = std::ostream;
	using io_stream = std::iostream;
	using in_file_stream = std::ifstream;
	using out_file_stream = std::ofstream;
	using io_file_stream = std::fstream;
}
#endif	// NWL_IO_STREAM_H