#ifndef NWL_STRING_H
#define NWL_STRING_H

#include <nwl_core.hpp>

namespace NWL
{
	using String = std::string;
	using WString = std::wstring;
	using StrStream = std::stringstream;
}

namespace NWL
{
	inline const char* CStrGetDelimR(const char* strSource, char cDelim, Size szOffset = 0) {
		String strRes(strSource);
		return &strRes[0];
	}
	inline String StrGetFormat(const char* strFormat, ...) {
		StrStream strRes;
		va_list argList;
		va_start(argList, strFormat);
		Size nCurr = 0;
		Char cCurr = strFormat[nCurr];
		for (; cCurr != '\0'; cCurr = strFormat[++nCurr]) {
			if (cCurr == '%') {
				cCurr = strFormat[++nCurr];
				switch (cCurr) {
				case 's': strRes << va_arg(argList, const char*); break;
				case 'd': strRes << va_arg(argList, int); break;
				case 'f': strRes << va_arg(argList, float); break;
				case '%': strRes << cCurr; break;
				default: NWL_ERR("Error format!"); return &strRes.str()[0]; break;
				}
			}
			else { strRes << cCurr; }
		}
		va_end(argList);
		return &strRes.str()[0];
	}
	template<typename ... Args>
	inline const char* CStrGetFormat(const char* strFormat, Args&& ... Arguments) { return &StrGetFormat(strFormat, std::forward<Args>(Arguments)...)[0]; }
}

#endif // NWL_STRING_H