#include <nwl_pch.hpp>
#include "data_res.h"

namespace NWL
{
	// --==<ADataRes>==--
	ADataRes::ADataRes(const char* strName, UInt32 tId) :
		m_drId(0), m_tId(tId), m_strName(strName) { }
	ADataRes::~ADataRes() { }
	// --setters
	void ADataRes::SetName(const char* strName) { m_strName = strName; }
	// --core_methods
	// --==</ADataRes>==--
}