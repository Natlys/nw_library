#include <nwl_pch.hpp>
#include "mem_sys.h"

NWL::mem_arena NWL::mem_sys::s_memory = NWL::mem_arena(nullptr, 0);

namespace NWL
{
	// --==<core_methods>==--
	void mem_sys::on_init(size memory_size) {
		if (s_memory.get_data() != nullptr) { return; }
		s_memory = mem_arena(new sbyte[memory_size], memory_size);
	}
	void mem_sys::on_quit() {
		if (s_memory.get_data() == nullptr) { return; }
		delete[] s_memory.get_data();
		s_memory = mem_arena(nullptr, 0);
	}
	// --==</core_methods>==--
}