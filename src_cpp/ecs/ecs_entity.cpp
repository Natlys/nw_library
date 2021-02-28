#include <nwl_pch.hpp>
#include "ecs_entity.h"
#include <ecs/ecs_cmp_sys.h>

NWL::IdStack NWL::AEnt::s_idStack = IdStack(1);

namespace NWL
{
	AEnt::AEnt(UInt32 tId) :
		m_eId(s_idStack.GetFreeId()), m_tId(tId),
		m_bIsEnabled(true) { }
	AEnt::~AEnt() {
		auto& rCmps = CmpSys::GetEntCmps(m_eId);
		while (!rCmps.empty()) { CmpSys::RmvCmp(m_eId, rCmps.begin()->first); }
		CmpSys::GetEntCmpRegistry().erase(m_eId);
		s_idStack.SetFreeId(m_eId);
	}
	// --setters
	void AEnt::SetEnabled(Bit bIsEnabled) { m_bIsEnabled = bIsEnabled; }
}