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
	NWL_API String StrGetFormatVa(const char* strFormat, va_list& argList);
	NWL_API String StrGetFormat(const char* strFormat, ...);
	NWL_API const char* CStrGetPartL(const char* strSource, char cDelim, int nFromL = 0);
	NWL_API const char* CStrGetPartR(const char* strSource, char cDelim, int nFromR = 0);
	NWL_API const char* CStrGetFormat(const char* strFormat, ...);
	NWL_API bool CStrIsEqual(const char* strL, const char* strR);
}
#endif // NWL_STRING_H