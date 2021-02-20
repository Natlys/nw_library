#include <nwl_pch.hpp>
#include "ecs_ent_sys.h"

namespace NWL
{
	void EntSys::OnInit() {
	}
	void EntSys::OnQuit()
	{
		GetRegistry().clear();
	}
}