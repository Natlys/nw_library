#include "nwl_memory.h"

void* operator new(Size szAlloc)								{ NWL::MemInfo::GetGlobal().SetAllocation(szAlloc, 1); return malloc(szAlloc); }
void* operator new[](Size szAlloc)								{ NWL::MemInfo::GetGlobal().SetAllocation(szAlloc, 1); return malloc(szAlloc); }
void operator delete(void* pBlock, Size szDealloc) throw()		{ NWL::MemInfo::GetGlobal().SetDeallocation(szDealloc, 1); free(pBlock); }
void operator delete[](void* pBlock, Size szDealloc) throw()	{ NWL::MemInfo::GetGlobal().SetDeallocation(szDealloc, 1); free(pBlock); }