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
	inline UInt32 StrLen(const char* cString);

	inline Int32 StrFindL(const char* cSource, const char cFind);
	inline Int32 StrFindR(const char* cSource, const char cFind);

	inline const char* GetStringPart(const char* cSource, UInt32 unBegin);
	inline const char* GetStringPart(const char* cSource, UInt32 unBegin, UInt32 unEnd);
}

namespace NWL
{
	//
}

#endif // NWL_STRING_H