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
	String StrGetFormatVa(const char* strFormat, va_list& argList);
	String StrGetFormat(const char* strFormat, ...);
	const char* CStrGetDelimR(const char* strSource, char cDelim, Size szOffset = 0);
	const char* CStrGetFormat(const char* strFormat, ...);
	bool CStrIsEqual(const char* strL, const char* strR);
}

#endif // NWL_STRING_H