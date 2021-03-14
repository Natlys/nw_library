#ifndef NW_INFO_H
#define NW_INFO_H
#include <nwl_core.hpp>
#include <io/io_stream.h>
#include <core/nwl_string.h>
namespace NW
{
	/// abstract info struct
	class NW_API a_info
	{
	public:
		a_info();
		virtual ~a_info() = default;
		// --operators
		virtual out_stream& operator<<(out_stream& stm) const = 0;
		virtual in_stream& operator>>(in_stream& stm) = 0;
	};
	out_stream& operator<<(out_stream& stm, a_info& info);
	in_stream& operator>>(in_stream& stm, a_info& info);
}
#endif	// NW_INFO_H