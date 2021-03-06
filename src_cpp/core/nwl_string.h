#ifndef NWL_STRING_H
#define NWL_STRING_H
#include <nwl_core.hpp>
namespace NWL
{
	using cstring = const char*;
	using dstring = std::string;
	using str_stream = std::stringstream;
	using cstring16 = const wchar_t*;
	using dstring16 = std::wstring;
}
namespace NWL
{
	NWL_API dstring str_format_var(cstring format, va_list& arg_list);
	NWL_API dstring str_format(cstring format, ...);
	NWL_API cstring str_part_left(cstring source, schar delim_char, ui32 from_left = 0);
	NWL_API cstring str_part_right(cstring source, schar delim_char, ui32 from_right = 0);
	NWL_API bit str_is_equal(cstring str0, cstring str1);
}
#endif // NWL_STRING_H