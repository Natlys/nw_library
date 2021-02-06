#include "nwl_data_res.h"


namespace NWL
{
	// --==<ADataRes>==--
	ADataRes::ADataRes(const char* strName, UInt32 unId) :
		m_unId(unId), m_strName(strName) { }
	ADataRes::~ADataRes() { }

	// --setters
	void ADataRes::SetName(const char* strName) { m_strName = strName; }
	// --==</ADataRes>==--
}