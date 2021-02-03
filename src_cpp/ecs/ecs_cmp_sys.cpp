#include <nwl_pch.hpp>
#include "ecs_cmp_sys.h"

namespace NWL
{
	void CmpSys::OnInit() {
		GetMemory() = MemArena(MemSys::GetMemory().Alloc(1 << 18), 1 << 18);
	}
	void CmpSys::OnQuit() {
		MemSys::GetMemory().Dealloc(GetMemory().GetDataBeg(), GetMemory().GetDataSize());
		GetMemory() = MemArena(nullptr, 0);
	}
}