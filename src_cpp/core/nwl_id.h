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
		void set_free_id(ui32 free_id);
	};
}
namespace NWL
{
	/// id_indexator class
	class NWL_API id_indexator
	{
	public:
		template<typename itype> static ui32 get_id()				{ return get_id_stack<itype>().get_free_id(); }
		template<typename itype> static void set_id(ui32 id)		{ get_id_stack<itype>().set_free_id(id); }
	private:
		template<typename itype> static id_stack& get_id_stack()	{ static id_stack s_id_stack(0); return s_id_stack; }
	};
}
namespace NWL
{
	/// id_owner class
	class NWL_API a_id_owner
	{
	public:
		a_id_owner();
		virtual ~a_id_owner();
		// --getters
		virtual inline ui32 get_id() = 0;
	};
}
#endif	// NWL_ID_STACK_H