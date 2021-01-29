#include "nwl_data_res.h"

NWL::IdStack NWL::ADataRes::s_IdStack = NWL::IdStack();
NWL::ADataRes::ADRs NWL::ADataRes::s_ADRs;

namespace NWL
{
	// --==<ADataRes>==--
	ADataRes::ADataRes(const char* strName) :
		m_unId(0), m_strName(strName)
	{
		m_unId = s_IdStack.GetFreeId();
		AddADataRes(this);
	}
	ADataRes::ADataRes(const char* strName, UInt32 unId) :
		m_unId(unId), m_strName(strName)
	{
		AddADataRes(this);
	}
	ADataRes::~ADataRes()
	{
		s_IdStack.SetFreeId(m_unId);
		RmvADataRes(GetId());
	}

	// --setters
	void ADataRes::SetName(const char* strName) {
		m_strName = strName;
	}
	// --core_methods
	void ADataRes::AddADataRes(ADataRes* pDataRes) {
		if (pDataRes == nullptr) { return; }
		s_ADRs[pDataRes->GetId()] = pDataRes;
	}
	void ADataRes::RmvADataRes(UInt32 unId) {
		ADRs::iterator itDR = s_ADRs.find(unId);
		if (itDR == s_ADRs.end()) { return; }
		s_ADRs.erase(itDR);
	}
	// --==</ADataRes>==--
}