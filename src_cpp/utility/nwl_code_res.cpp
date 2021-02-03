#include <nwl_pch.hpp>
#include "nwl_code_res.h"

namespace NWL
{
	// --==<ACodeRes>==--
	ACodeRes::ACodeRes(const char* strName) :
		TDataRes<ACodeRes>(strName), m_strCode("") { }
	ACodeRes::~ACodeRes() { }
	// --==</ACodeRes>==--
}