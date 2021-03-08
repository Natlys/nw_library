#include <nwl_pch.hpp>
#include "nwl_id.h"

namespace NWL
{
	void id_stack::set_free_id(ui32 free_id) { if (free_id != top()) { push(free_id); } }
}
namespace NWL
{
	a_id_owner::a_id_owner() { }
	a_id_owner::~a_id_owner() { }
}