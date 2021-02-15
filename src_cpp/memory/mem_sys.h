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
		// --core_methods
		static inline void OnInit(Size szMemory = 1 << 20);
		static inline void OnQuit();
		static inline Ptr Alloc(Size szData, Size szAllign = sizeof(MemLink)) { return GetMemory().Alloc(szData, szAllign); }
		static inline void Dealloc(Ptr pData, Size szData) { GetMemory().Dealloc(pData, szData); }
		// --templated_methods
		template<typename MType, typename ... Args>
		static inline MType* NewT(Args&& ... Arguments);
		template<typename MType>
		static inline MType* NewTArr(UInt64 unAlloc);
		template<typename MType>
		static inline void DelT(MType* pBlock);
		template <typename MType>
		static inline void DelTArr(MType* pBlock, UInt64 unDealloc);
	};
	// --core_methods
	inline void MemSys::OnInit(Size szMemory) {
		if (GetMemory().GetDataBeg() != nullptr) { return; }
		GetMemory() = MemArena(new Byte[szMemory], szMemory);
	}
	inline void MemSys::OnQuit() {
		if (GetMemory().GetDataBeg() == nullptr) { return; }
		delete[] GetMemory().GetDataBeg();
		GetMemory() = MemArena(nullptr, 0);
	}
	// --templated_methods
	template<typename MType, typename ... Args>
	inline MType* MemSys::NewT(Args&& ... Arguments) { return GetMemory().NewT<MType>(std::forward<Args>(Arguments)...); }
	template <typename MType>
	inline MType* MemSys::NewTArr(UInt64 unAlloc) { return GetMemory().NewTArr<MType>(unAlloc); }
	template<typename MType>
	inline void MemSys::DelT(MType* pBlock) { GetMemory().DelT<MType>(pBlock); }
	template <typename MType>
	inline void MemSys::DelTArr(MType* pBlock, UInt64 unDealloc) { GetMemory().DelTArr<MType>(pBlock, unDealloc); }
}

#endif	// NWL_MEMORY_SYSTEM_H