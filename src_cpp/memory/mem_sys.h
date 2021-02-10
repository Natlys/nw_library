#ifndef NWL_MEMORY_SYSTEM_H
#define NWL_MEMORY_SYSTEM_H

#include <nwl_core.hpp>

#include <memory/mem_allocator.h>

namespace NWL
{
	/// MemorySystem static class
	class NWL_API MemSys
	{
	public:
		// --getters
		static inline AMemAllocator& GetMemory() { static MemArena s_Memory; return s_Memory; }
		static inline const MemInfo& GetInfo() { return GetMemory().GetInfo(); }
		// --setters
		// --core_methods
		static inline void OnInit(Size szMemory = 1 << 20);
		static inline void OnQuit();
	};
	inline void MemSys::OnInit(Size szMemory) {
		if (GetMemory().GetDataBeg() != nullptr) { return; }
		GetMemory() = MemArena(new Byte[szMemory], szMemory);
	}
	inline void MemSys::OnQuit() {
		if (GetMemory().GetDataBeg() == nullptr) { return; }
		delete[] GetMemory().GetDataBeg();
		GetMemory() = MemArena(nullptr, 0);
	}
	template<typename MType, typename ... Args>
	static inline MType* NewT(Args ... Arguments) {
		MType* pBlock = reinterpret_cast<MType*>(MemSys::GetMemory().Alloc(1 * sizeof(MType), __alignof(MType)));
		NewPlaceT<MType>(pBlock, std::forward<Args>(Arguments)...);
		return pBlock;
	}
	template <typename MType>
	static inline MType* NewTArr(UInt64 unAlloc) {
		return reinterpret_cast<MType*>(MemSys::GetMemory().Alloc(unAlloc * sizeof(MType), __alignof(MType)));
	}
	template<typename MType>
	static inline void DelT(MType* pBlock) {
		pBlock->~MType();
		MemSys::GetMemory().Dealloc(pBlock, 1 * sizeof(MType));
	}
	template <typename MType>
	static inline void DelTArr(MType* pBlock, UInt64 unDealloc) {
		for (Size bi = 0; bi < unDealloc; bi++) { pBlock[bi].~MType(); }
		MemSys::GetMemory().Dealloc(pBlock, unDealloc * sizeof(MType));
	}
}

#endif	// NWL_MEMORY_SYSTEM_H