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
	inline const char* SubStrDelimR(const char* strSource, char cDelim, UInt64 nOffset = 0) {
		return "";
	}
}

namespace NWL
{
	//
}

#endif // NWL_STRING_H