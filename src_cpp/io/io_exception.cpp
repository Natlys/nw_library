#include <nwl_pch.hpp>
#include "io_exception.h"

namespace NWL
{
	Exception::Exception(const char* strComment, UInt32 unCode, const char* strLoc, UInt32 unLine) :
		m_strComment(strComment), m_strLocation(strLoc), m_unCode(unCode), m_unLine(unLine) { NWL_ERR(GetStr()); }
	// --getters
	inline const char* Exception::GetStr() {
		StrStream stm;
		this->operator<<(stm);
		return &(stm.str())[0];
	}
	// --operators
	std::ostream& Exception::operator<<(std::ostream& rStream) {
		return rStream <<
			"--==<exception_info>==--" << std::endl <<
			"string: " << GetCom() << std::endl <<
			"code: " << GetCode() << std::endl <<
			"location: " << GetLoc() << std::endl <<
			"line: " << GetLine() << std::endl <<
			"--==</exception_info>==--" << std::endl;
	}
	std::istream& Exception::operator>>(std::istream& rStream) {
		rStream >> m_strComment;
		rStream >> m_strLocation;
		rStream >> m_unCode;
		rStream >> m_unLine;
		return rStream;
	}
	std::istream& operator>>(std::istream& rStream, Exception& rExc) { return rExc.operator>>(rStream); }
	std::ostream& operator<<(std::ostream& rStream, Exception& rExc) { return rExc.operator<<(rStream); }
}
#if (defined NWL_PLATFORM_WINDOWS)
namespace NWL
{
	WinException::WinException(const char* strInfo, UInt32 nCode, const char* strLoc, UInt32 nLine) :
		Exception(strInfo, nCode, strLoc, nLine) { }
}
#endif	// NWL_PLATFORM