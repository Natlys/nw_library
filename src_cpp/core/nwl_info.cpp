#include <nwl_pch.hpp>
#include "nwl_info.h"
namespace NW
{
	a_info::a_info()
	{
	}
	// --setters
	// --operators
	out_stream& operator<<(out_stream& stm, a_info& info) { return info.operator<<(stm); }
	in_stream& operator>>(in_stream& stm, a_info& info) { return info.operator>>(stm); }
}