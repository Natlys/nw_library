#ifndef NWL_STRING_H
#define NWL_STRING_H

#include <nwl_core.hpp>

#include <string>
#include <string.h>
#include <sstream>

namespace NWL
{
	using String = std::string;
	using WString = std::wstring;
	using StrStream = std::stringstream;
}

namespace NWL
{
	Int32 StrFindL(const char* cSource, char cFind);
	Int32 StrFindR(const char* cSource, char cFind);

	const char* SubStr(const char* strSource, Size nBeg);
	const char* SubStr(const char* strSource, Size nBeg, Size nEnd);

	const char* SubStrDelimR(const char* strSource, char cDelim, Int32 nStepFromDelim = 0);
}

namespace NWL
{
	//
}

#endif // NWL_STRING_H