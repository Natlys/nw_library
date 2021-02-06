#ifndef NWL_ID_STACK_H
#define NWL_ID_STACK_H

#include <nwl_core.hpp>

#include <nwlib/nwl_container.h>

namespace NWL
{
	/// IdStack class
	/// Description:
	/// --It's like a simple stack of unsigned 32-bit integers but for identificators
	/// --Contains one single ID for any class
	/// --You can get new id during construction of and object and put it back into the stack
	/// --If any destroyed instance gives back own ID to the stack - there is no loss
	class NWL_API IdStack : protected DStack<UInt32>
	{
	public:
		IdStack(UInt32 nBegin = 0) : DStack<UInt32>() { push(nBegin); }
		// -- getters
		inline UInt32 GetFreeId() { UInt32 unFreeId = top(); if (size() == 1) { top()++; } else { pop(); } return unFreeId; }
		// -- setters
		inline void SetFreeId(UInt32 unFreeId) { if (unFreeId != top()) { push(unFreeId); } }
	};
}
#endif	// NWL_ID_STACK_H