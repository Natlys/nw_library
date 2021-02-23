#include <nwl_pch.hpp>
#include "ecs_cmp_sys.h"

NWL::CmpSys::CmpsRegistry NWL::CmpSys::s_cReg = CmpsRegistry();

namespace NWL
{
	// --setters
	void CmpSys::RmvCmp(UInt32 eId, UInt32 tId) {
		if (!HasCmp(eId, tId)) { return; }
		GetRegistry()[eId].erase(tId);
	}
	// --==<core_methods>==--
	void CmpSys::OnInit() {
		if (!GetRegistry().empty()) { return; }
	}
	void CmpSys::OnQuit() {
		if (GetRegistry().empty()) { return; }
		GetRegistry().clear();
	}
	// --==</core_methods>==--
}