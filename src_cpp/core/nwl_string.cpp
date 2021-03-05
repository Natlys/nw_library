#include <nwl_pch.hpp>
#include "nwl_string.h"
namespace NWL
{
	dstring str_format_var(cstring format, va_list& arg_list) {
		char8 ccurr = ' ';
		size ncurr = 0;
		size nlen = strlen(format);
		dstring result;

		while (ncurr < nlen) {
			ccurr = format[ncurr++];
			switch (ccurr) {
			case '%':
				switch (ccurr = format[++ncurr]) {
				case '%': result.back() = ccurr; break;

				case 's': switch (ccurr = format[++ncurr]) {
				case 'b': _itoa_s(va_arg(arg_list, si8), &result.back(), result.size(), 10); break;
				case 's': _itoa_s(va_arg(arg_list, si16), &result.back(), result.size(), 10); break;
				case 'i': _itoa_s(va_arg(arg_list, si32), &result.back(), result.size(), 10); break;
				case 'l': _itoa_s(va_arg(arg_list, si64), &result.back(), result.size(), 10); break;
				default: return result;
					break;
				}
						break;

				case 'u': switch (ccurr = format[++ncurr]) {
				case 'b': _itoa_s(va_arg(arg_list, ui8), &result.back(), result.size(), 10); break;
				case 's': _itoa_s(va_arg(arg_list, ui16), &result.back(), result.size(), 10); break;
				case 'i': _itoa_s(va_arg(arg_list, ui32), &result.back(), result.size(), 10); break;
				case 'l': _itoa_s(va_arg(arg_list, ui64), &result.back(), result.size(), 10); break;
				default: return result;
				}
						break;

				case 'f': switch (ccurr = format[++ncurr]) {
				case 'f': result += std::to_string(va_arg(arg_list, f32)); break;
				case 'd': result += std::to_string(va_arg(arg_list, f64));  break;
				default: return result; break;
				}
						break;
				case 'c': switch (ccurr = format[++ncurr]) {
				case 's': result += va_arg(arg_list, cstring); break;
				default: return result; break;
				}
						break;
				default: return result; break;
				}
				break;
			default: result.push_back(ccurr); break;
			}
		}
		result.push_back('\0');
		return result;
	}
	dstring str_format(cstring format, ...) {
		va_list arg_list;
		va_start(arg_list, format);
		dstring result = str_format_var(format, arg_list);
		va_end(arg_list);
		return result;
	}
	cstring str_part_left(cstring source, char8 delim_char, ui32 offset_from_left) {
		si32 length = strlen(source);
		if (length == 0) { return ""; }
		si32 ncurr = offset_from_left % length;
		while (source[ncurr] != delim_char && ncurr <= length) { ncurr += 1; }
		return &source[ncurr];
	}
	cstring str_part_right(cstring source, char8 delim_char, ui32 offset_from_right) {
		si32 length = strlen(source);
		if (length == 0) { return ""; }
		si32 ncurr= length - (offset_from_right % length);
		while (source[ncurr] != delim_char && ncurr <= length) { ncurr -= 1; }
		return &source[ncurr];
	}
	bit str_is_equal(cstring str0, cstring str1) {
		size ncurr = 0;
		while(str0[ncurr++] != '\0') { if (str0[ncurr] != str1[ncurr]) { return false; } }
		return true;
	}
}