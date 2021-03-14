#ifndef NW_STRING_H
#define NW_STRING_H
#include <nwl_core.hpp>
namespace NW
{
	using cstring = const char*;
	using dstring = std::string;
	using io_stream_str = std::stringstream;
	using cstring16 = const wchar_t*;
	using dstring16 = std::wstring;
}
namespace NW
{
	NW_API dstring str_format_var(cstring format, va_list& arg_list);
	NW_API dstring str_format(cstring format, ...);
	NW_API cstring str_part_left(cstring source, schar delim_char, ui32 from_left = 0);
	NW_API cstring str_part_right(cstring source, schar delim_char, ui32 from_right = 0);
	NW_API bit str_is_equal(cstring str0, cstring str1);
}
#endif // NW_STRING_H