#include <nwl_pch.hpp>
#include "ecs_ent_sys.h"

namespace NWL
{
	void EntSys::OnInit() {
		GetMemory() = MemArena(MemSys::GetMemory().Alloc(1 << 18), 1 << 18);
	}
	void EntSys::OnQuit()
	{
		GetEnts().clear();
		MemSys::GetMemory().Dealloc(GetMemory().GetDataBeg(), GetMemory().GetDataSize());
		GetMemory() = MemArena(nullptr, 0);
	}
}