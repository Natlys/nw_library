#include <nwl_pch.hpp>
#include "io_exception.h"

namespace NWL
{
	Exception::Exception(const char* strInfo, UInt32 nCode, const char* strLoc, UInt32 nLine) :
		m_strInfo(CStrGetFormat("CORE_EXCEPTION::INFO_%s::CODE_%d::LOCATION_%s::LINE_%d\n",
			&strInfo[0], nCode, &strLoc[0], nLine)),
		m_unErrCode(nCode) { }
	Exception::~Exception() { }
}