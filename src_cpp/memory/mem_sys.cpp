#include <nwl_pch.hpp>
#include "mem_sys.h"

NW::mem_arena NW::mem_sys::s_memory = NW::mem_arena(nullptr, 0);

namespace NW
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