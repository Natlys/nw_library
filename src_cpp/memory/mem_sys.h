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
		static void OnInit(Size szMemory = 1 << 20);
		static void OnQuit();
		static inline Ptr Alloc(Size szData, Size szAllign = sizeof(MemLink)) { return GetMemory().Alloc(szData, szAllign); }
		static inline void Dealloc(Ptr pData, Size szData) { GetMemory().Dealloc(pData, szData); }
		// --templated_methods
		template<typename MType, typename ... Args> static inline MType* NewT(Args&& ... Arguments);
		template<typename MType> static inline MType* NewTArr(UInt64 unAlloc);
		template<typename MType> static inline void DelT(MType* pBlock);
		template <typename MType> static inline void DelTArr(MType* pBlock, UInt64 unDealloc);
	};
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
namespace NWL
{
	/// Abstract MemorySystemUser
	class NWL_API AMemUser
	{
	public:
		// --operators
		inline void* operator new(Size szData, Ptr pBlock) { return ::operator new(szData, pBlock); }
		inline void* operator new(Size szData) { return MemSys::Alloc(szData); }
		inline void* operator new[](Size szData) { return MemSys::Alloc(szData); }
		inline void operator delete(Ptr pBlock, Size szData) { MemSys::Dealloc(pBlock, szData); }
		inline void operator delete[](Ptr pBlock, Size szData) { MemSys::Dealloc(pBlock, szData); }
	};
}

#endif	// NWL_MEMORY_SYSTEM_H