#ifndef NWL_MEMORY_ALLOCATOR_H
#define NWL_MEMORY_ALLOCATOR_H

#include <nwl_core.hpp>

namespace NWL
{
	/// MemInfo struct
	struct NWL_API MemInfo
	{
	public:
		Size szMem = 0;
		UInt64 unMem = 0;
		Size szAlloc = 0;
		UInt64 unAlloc = 0;
		Ptr pLoc = this;
	public:
		// --getters
		inline uintptr_t GetLocNum(Size szOffset = 0) const { return reinterpret_cast<uintptr_t>(pLoc) + szOffset; }
		// --setters
		void SetAllocation(Size szData, UInt64 unData);
		void SetDeallocation(Size szData, UInt64 unData);
		// --operators
		std::ostream& operator<<(std::ostream& rStream) const;
	};
	/// MemLink struct
	struct NWL_API MemLink
	{
	public:
		MemLink* pNext = nullptr;
		Size szBlock = 0;
	public:
		// --getters
		MemLink* GetBlock(Size szMem);
		// --operators
		template <typename MType> inline operator MType*() { return reinterpret_cast<MType*>(this); }
	};
}

namespace NWL
{
	/// Abstract MemAllocator class
	class NWL_API AMemAllocator
	{
	public:
		AMemAllocator(Ptr pBlock = nullptr, Size szMemory = 0ul);
		virtual ~AMemAllocator();
		// --getters
		inline Ptr GetDataBeg()	{ return &m_pBeg[0]; }
		inline Ptr GetDataCur()	{ return &m_pBeg[m_Info.szAlloc]; }
		inline Ptr GetDataEnd()	{ return &m_pBeg[m_Info.szMem]; }
		inline Size GetDataSize() const			{ return m_Info.szMem; }
		inline Size GetAllocSize() const		{ return m_Info.szAlloc; }
		inline UInt64 GetAllocCount() const		{ return m_Info.unAlloc; }
		inline Size GetFreeSize() const			{ return m_Info.szMem - m_Info.szAlloc; }
		inline UInt64 GetFreeCount() const		{ return m_Info.unMem - m_Info.unAlloc; }
		inline const MemInfo& GetInfo() const	{ return m_Info; }
		// --predicates
		inline bool HasBlock(Ptr pBlock) const	{ return (pBlock >= &m_pBeg[0]) && (pBlock <= &m_pBeg[m_Info.szMem]); }
		inline bool HasEnoughSize(Size szHowMuch)const	{ return GetFreeSize() > szHowMuch; }
		inline bool HasEnoughCount(Size szHowMuch) { return GetFreeCount() > szHowMuch; }
		// --core_methods
		virtual Ptr Alloc(Size szMem, Size szAlign = sizeof(int)) = 0;
		virtual void Dealloc(Ptr pBlock, Size szDealloc) = 0;
		virtual Ptr Realloc(Ptr pBlock, Size szOld, Size szNew) = 0;
		template<typename MType, typename ... Args> MType* NewT(Args&& ... Arguments);
		template<typename MType> MType* NewTArr(UInt64 unAlloc);
		template<typename MType> void DelT(MType* pBlock);
		template<typename MType> void DelTArr(MType* pBlock, UInt64 unDealloc);
	protected:
		Byte* m_pBeg;
		MemInfo m_Info;
	};
	template<typename MType, typename ... Args> MType* AMemAllocator::NewT(Args&& ... Arguments) {
		MType* pBlock = reinterpret_cast<MType*>(Alloc(1ul * sizeof(MType), __alignof(MType)));
		new(pBlock) MType(std::forward<Args>(Arguments)...);
		return pBlock;
	}
	template <typename MType> MType* AMemAllocator::NewTArr(UInt64 unAlloc) {
		return reinterpret_cast<MType*>(Alloc(unAlloc * sizeof(MType), __alignof(MType)));
	}
	template<typename MType> void AMemAllocator::DelT(MType* pBlock) {
		pBlock->~MType();
		rmAllocator.Dealloc(pBlock, 1 * sizeof(MType));
	}
	template <typename MType> void AMemAllocator::DelTArr(MType* pBlock, UInt64 unDealloc) {
		if (unDealloc >= GetDataSize()) { unDealloc = GetDataSize(); }
		for (Size bi = 0; bi < unDealloc; bi++) { pBlock[bi].~MType(); }
		Dealloc(pBlock, unDealloc * sizeof(MType));
	}
}
namespace NWL
{
	/// MemArena class
	/// Description:
	/// --Just a chunk of bytes works with Ptr and char* pointers
	class NWL_API MemArena : public AMemAllocator
	{
	public:
		MemArena(Ptr pBlock = nullptr, Size szMemory = 0ul);
		virtual ~MemArena();
		// --core_methods
		virtual Ptr Alloc(Size szMemory, Size szAlign = sizeof(MemLink)) override;
		virtual void Dealloc(Ptr pBlock, Size szDealloc) override;
		virtual Ptr Realloc(Ptr pBlock, Size szOld, Size szNew) override;
	private:
		MemLink* m_FreeList;
	};
}
namespace NWL
{
	/// LinearMemoryAllocator class
	class LinearAllocator : public AMemAllocator
	{
	public:
		LinearAllocator(Ptr pBlock = nullptr, Size szMemory = 0ul);
		virtual ~LinearAllocator();
		// --core_methods
		virtual Ptr Alloc(Size szMemory, Size szAlign = 4ul) override;
		virtual void Dealloc(Ptr pBlock, Size szDealloc) override;
		virtual Ptr Realloc(Ptr pBlock, Size szOld, Size szNew) override;
		void Clear();
	};
}
#endif	// NWL_MEMORY_ALLOCATOR_H