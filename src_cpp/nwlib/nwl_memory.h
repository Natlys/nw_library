#ifndef NWL_MEMORY_H
#define NWL_MEMORY_H

#include <nwl_core.hpp>

#include <memory>
#include <nwlib/nwl_io.h>

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
		inline UInt32 GetLocDec() const { return reinterpret_cast<uintptr_t>(pLoc); }
		// --operators
		OutStream& operator<<(OutStream& rStream) const;
	};
	inline OutStream& MemInfo::operator<<(OutStream& rStream) const {
		return rStream << "MEMORY_INFO::" << std::endl <<
			"address: " << std::hex << GetLocDec() << std::dec << std::endl <<
			"total bytes: " << szMem << std::endl <<
			"total blocks: " << unMem << std::endl <<
			"allocated bytes: " << szAlloc << std::endl <<
			"allocated blocks: " << unAlloc << std::endl;
	}
	inline OutStream& operator<<(OutStream& rStream, const MemInfo& rInfo) { return rInfo.operator<<(rStream); }
	/// MemLink struct
	struct NWL_API MemLink
	{
	public:
		MemLink* pNext = nullptr;
		UInt32 szBlock = 0;
	public:
		// --getters
		inline MemLink* GetBlock(UInt32 szMem) {
			if (szBlock >= szMem) { this->szBlock -= szMem; return this; }
			for (MemLink *pBlock = this, *pBlockNext = pBlock->pNext;
				pBlockNext != nullptr;
				pBlock = pBlockNext, pBlockNext = pBlockNext->pNext)
			{
				if (pBlockNext->szBlock >= szMem) {
					pBlock->szBlock -= szMem;
					if (pBlock->szBlock == 0) { pBlock->pNext = pBlockNext->pNext; }
					return pBlockNext;
				}
			}
			return nullptr;
		}
		template <typename MType>
		inline MType* GetCasted() { return reinterpret_cast<MType*>(this); }
	};
}
namespace NWL
{
	/// Abstract MemAllocator class
	class NWL_API AMemAllocator
	{
	public:
		AMemAllocator(Ptr pBlock, Size szMem) :
			m_pBeg(static_cast<Byte*>(pBlock)), m_Info(MemInfo())
		{
			m_Info.szMem = m_Info.unMem = szMem;
			m_Info.szAlloc = 0; m_Info.unAlloc = 0;
			m_Info.pLoc = pBlock;
		}
		virtual ~AMemAllocator() { NWL_ASSERT(GetAllocSize() == 0 && GetAllocCount() == 0, "memory leak"); }

		// --getters
		inline Ptr GetDataBeg() { return &m_pBeg[0]; }
		inline Ptr GetDataCur() { return &m_pBeg[m_Info.unAlloc]; }
		inline Ptr GetDataEnd() { return &m_pBeg[m_Info.szMem]; }
		inline Size GetDataSize() const { return m_Info.szMem; }
		inline Size GetAllocSize() const { return m_Info.szAlloc; }
		inline UInt64 GetAllocCount() const { return m_Info.unAlloc; }
		inline Size GetFreeSize() { return m_Info.szMem - m_Info.szAlloc; }
		inline UInt64 GetFreeCount() { return m_Info.unMem - m_Info.unAlloc; }
		inline const MemInfo& GetInfo() const { return m_Info; }
		// --predicates
		inline bool HasBlock(Ptr pBlock) { return (pBlock >= GetDataBeg()) && (pBlock <= GetDataEnd()); }
		inline bool HasEnoughSize(Size szHowMuch) { return GetFreeSize() > szHowMuch; }
		inline bool HasEnoughCount(Size szHowMuch) { return GetFreeCount() > szHowMuch; }
		// --core_methods
		virtual inline Ptr Alloc(Size szMem, UInt8 szAlign = 4) = 0;
		virtual inline void Dealloc(Ptr pBlock, Size szDealloc) = 0;
		virtual inline Ptr Realloc(Ptr pBlock, Size szOld, Size szNew) = 0;
	protected:
		Byte* m_pBeg;
		MemInfo m_Info;
	};
}
namespace NWL
{
	/// MemArena class
	/// Description:
	/// --Just a chunk of bytes works with Ptr and char* pointers
	class NWL_API MemArena : public AMemAllocator
	{
	public:
		MemArena(Ptr pBlock, Size szMemory) :
			AMemAllocator(pBlock, szMemory),
			m_FreeList(nullptr) { }
		~MemArena() { }

		// --core_methods
		virtual inline Ptr Alloc(Size szMemory, UInt8 szAlign = sizeof(MemLink)) override;
		virtual inline void Dealloc(Ptr pBlock, Size szDealloc) override;
		virtual inline Ptr Realloc(Ptr pBlock, Size szOld, Size szNew) override;
	private:
		MemLink* m_FreeList;
	};
	// --==<core_methods>==--
	inline Ptr MemArena::Alloc(Size szMemory, UInt8 szAlign) {
		Ptr pBlock = nullptr;
		if (szMemory == 0) { return nullptr; }
		szMemory = (szMemory + szAlign - 1) & ~(szAlign - 1);
		if (m_FreeList != nullptr) {
			if (MemLink* pLink = m_FreeList->GetBlock(szMemory)) {
				pBlock = pLink->GetCasted<Byte>();
				if (pLink == m_FreeList && m_FreeList->szBlock == 0) { m_FreeList = m_FreeList->pNext; }
			}
			else {
				if (HasEnoughSize(szMemory)) { pBlock = &m_pBeg[szMemory]; }
				else { NWL_ERR("the memory is exhausted!"); }
			}
		}
		else {
			if (HasEnoughSize(szMemory)) { pBlock = &m_pBeg[GetAllocSize()]; }
			else { NWL_ERR("the memory is exhausted!"); }
		}
		m_Info.unAlloc++;
		m_Info.szAlloc += szMemory;
		return pBlock;
	}
	inline void MemArena::Dealloc(Ptr pBlock, Size szMemory) {
		if (HasBlock(pBlock)) {
			MemLink* pNextFreeList = reinterpret_cast<MemLink*>(pBlock);
			pNextFreeList->pNext = m_FreeList;
			pNextFreeList->szBlock = szMemory;
			m_FreeList = pNextFreeList;
		}
		else { NWL_ERR("the memory is exhausted!"); }
		memset(pBlock, 0, szMemory);
		m_Info.unAlloc--;
		m_Info.szAlloc -= szMemory;
	}
	inline Ptr MemArena::Realloc(Ptr pBlock, Size szOld, Size szNew) {
		Size szCpy = szOld < szNew ? szOld : szNew;
		Ptr pRealloc = Alloc(szNew);
		memcpy(pRealloc, pBlock, szCpy);
		Dealloc(pBlock, szOld);
		return pRealloc;
	}
	// --==</core_methods>==--
}
namespace NWL
{
	/// RefOwner class
	/// Description:
	/// -- Smart "unique" pointer in nw implementation
	/// -- Allocates object due to given allocator and frees it when gets deleted
	/// Interface:
	/// -> Create RefOwner -> MakeRef with particular allocator -> use as a pointer
	template <typename MType>
	class NWL_API RefOwner
	{
	public:
		RefOwner() :
			m_pAllocator(nullptr), m_pRef(nullptr), m_szData(0) { }
		RefOwner(RefOwner& rCpy) :
			m_pAllocator(rCpy.m_pAllocator), *m_pRef(*rCpy.m_pRef), m_szData(rCpy.m_szData) { }
		~RefOwner() { Reset(); }

		// --getters
		inline AMemAllocator* GetAllocator() { return m_pAllocator; }
		inline MType* GetRef() { return m_pRef; }
		inline Size GetSize() const { return m_szData; }
		// --setters
		inline void Reset();
		// --core_methods
		template <typename VType, typename...Args>
		inline void MakeRef(AMemAllocator& rAllocator, Args...Arguments) {
			Reset();
			m_pAllocator = &rAllocator;
			m_szData = sizeof(VType) + __alignof(VType);
			VType* pRef = static_cast<VType*>(m_pAllocator->Alloc(m_szData));
			new(pRef)VType(std::forward<Args>(Arguments)...);
			m_pRef = pRef;
		}
		template <typename VType>
		inline void MakeRef(AMemAllocator& rAllocator, VType& rCpy) {
			Reset();
			m_pAllocator = &rAllocator;
			m_szData = sizeof(sizeof(VType), __alignof(VType));
			new(m_pRef)VType(rCpy);
		}
		// --operators
		inline MType* operator->() { return m_pRef; }
		inline MType& operator*() { return *m_pRef; }
		inline void operator=(MType* pRef) = delete;
		inline void operator=(RefOwner& rCpy) {
			m_pAllocator = rCpy.m_pAllocator;
			*m_pRef = *rCpy.m_pRef;
			m_szData = rCpy.m_szData;
		}
	private:
		AMemAllocator* m_pAllocator;
		MType* m_pRef;
		Size m_szData;
	};
	// --setters
	template <typename MType>
	inline void RefOwner<MType>::Reset() {
		if (m_pRef != nullptr && m_pAllocator != nullptr) {
			m_pRef->~MType();
			m_pAllocator->Dealloc(m_pRef, m_szData);
		}
		m_pAllocator = nullptr;
		m_pRef = nullptr;
		m_szData = 0;
	}
}
#endif // NWL_MEMORY_H