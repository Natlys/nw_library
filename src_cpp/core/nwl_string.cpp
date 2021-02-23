#include <nwl_pch.hpp>
#include "nwl_string.h"

namespace NWL
{
	String StrGetFormatVa(const char* strFormat, va_list& argList) {
		Char cCurr = ' ';
		Size szCurr = 0;
		Size szLen = strlen(strFormat);
		String strRes;

		while (szCurr < szLen) {
			cCurr = strFormat[szCurr++];
			switch (cCurr) {
			case '%':
				switch (cCurr = strFormat[++szCurr]) {
				case '%': strRes.back() = cCurr; break;

				case 's': switch (cCurr = strFormat[++szCurr]) {
				case 'b': _itoa_s(va_arg(argList, Int8), &strRes.back(), strRes.size(), 10); break;
				case 's': _itoa_s(va_arg(argList, Int16), &strRes.back(), strRes.size(), 10); break;
				case 'i': _itoa_s(va_arg(argList, Int32), &strRes.back(), strRes.size(), 10); break;
				case 'l': _itoa_s(va_arg(argList, Int64), &strRes.back(), strRes.size(), 10); break;
				default: return strRes;
					break;
				}
						break;

				case 'u': switch (cCurr = strFormat[++szCurr]) {
				case 'b': _itoa_s(va_arg(argList, UInt8), &strRes.back(), strRes.size(), 10); break;
				case 's': _itoa_s(va_arg(argList, UInt16), &strRes.back(), strRes.size(), 10); break;
				case 'i': _itoa_s(va_arg(argList, UInt32), &strRes.back(), strRes.size(), 10); break;
				case 'l': _itoa_s(va_arg(argList, UInt64), &strRes.back(), strRes.size(), 10); break;
				default: return strRes;
				}
						break;

				case 'f': switch (cCurr = strFormat[++szCurr]) {
				case 'f': strRes += std::to_string(va_arg(argList, Float32)); break;
				case 'd': strRes += std::to_string(va_arg(argList, Float64));  break;
				default: return strRes; break;
				}
						break;
				case 'c': switch (cCurr = strFormat[++szCurr]) {
				case 's': strRes += va_arg(argList, const char*); break;
				default: return strRes; break;
				}
						break;
				default: return strRes; break;
				}
				break;
			default: strRes.push_back(cCurr); break;
			}
		}
		strRes.push_back('\0');
		return strRes;
	}
	String StrGetFormat(const char* strFormat, ...) {
		va_list argList;
		va_start(argList, strFormat);
		String strRes = StrGetFormatVa(strFormat, argList);
		va_end(argList);
		return strRes;
	}
}
namespace NWL
{
	const char* CStrGetDelimR(const char* strSource, char cDelim, Size szOffset) {
		Size szLen = strlen(strSource);
		Size szCurr = szLen - szOffset;
		while(strSource[--szCurr] != cDelim && szCurr <= szLen) { }
		return &strSource[szCurr];
	}
	const char* CStrGetFormat(const char* strFormat, ...) {
		va_list argList;
		va_start(argList, strFormat);
		String strRes = StrGetFormatVa(strFormat, argList);
		va_end(argList);
		return &strRes[0];
	}
	bool CStrIsEqual(const char* strL, const char* strR) {
		Size szCurr = 0;
		while(strL[szCurr++] != '\0') { if (strL[szCurr] != strR[szCurr]) { return false; } }
		return true;
	}
}