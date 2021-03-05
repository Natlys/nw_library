#ifndef NWL_ID_STACK_H
#define NWL_ID_STACK_H
#include <nwl_core.hpp>
namespace NWL
{
	/// id_stack class
	/// description:
	/// --it's like a simple stack of unsigned 32-bit integers but for identificators;
	/// --contains one single id for any class;
	/// --you can get new id during construction of and object and put it back into the stack;
	/// --if any destroyed instance gives back own id to the stack - there is no loss;
	class NWL_API id_stack : protected std::stack<ui32>
	{
	public:
		id_stack(ui32 first_id = 1) : std::stack<ui32>() { push(first_id); }
		// -- getters
		inline ui32 get_free_id() { ui32 free_id = top(); if (size() == 1) { top()++; } else { pop(); } return free_id; }
		// -- setters
		inline void set_free_id(ui32 free_id) { if (free_id != top()) { push(free_id); } }
	};
}
#endif	// NWL_ID_STACK_H