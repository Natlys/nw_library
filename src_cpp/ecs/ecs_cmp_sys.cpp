#include <nwl_pch.hpp>
#include "ecs_cmp_sys.h"
#include <ecs/ecs_ent_sys.h>

NWL::CmpSys::EntCmpRegistry NWL::CmpSys::s_ecReg;
NWL::CmpSys::TypeCmpRegistry NWL::CmpSys::s_tcReg;

namespace NWL
{
	// --==<core_methods>==--
	void CmpSys::OnInit() {
		if (!s_ecReg.empty() && !s_tcReg.empty()) { return; }
	}
	void CmpSys::OnQuit() {
		if (s_ecReg.empty() && s_tcReg.empty()) { return; }
		s_ecReg.clear();
		s_tcReg.clear();
	}

	void CmpSys::AddCmp(RefKeeper<ACmp>& rCmp) {
		s_ecReg[rCmp->GetEntId()][rCmp->GetTypeId()].SetRef(rCmp);
		s_tcReg[rCmp->GetTypeId()][rCmp->GetEntId()].SetRef(rCmp);
	}
	void CmpSys::RmvCmp(UInt32 eId, UInt32 tId) {
		if (!HasCmp(eId, tId)) { return; }
		s_ecReg[eId].erase(tId);
		s_tcReg[tId].erase(eId);
	}
	// --==</core_methods>==--
}