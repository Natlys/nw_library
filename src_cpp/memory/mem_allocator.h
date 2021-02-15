#ifndef NWL_MEMORY_ALLOCATOR_H
#define NWL_MEMORY_ALLOCATOR_H

#include <nwl_core.hpp>

namespace NWL
{
	inline Size GetAligned(Size szData, Size szAlign) { return (szData + (szAlign - 1)) & ~(szAlign - 1); }
}
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
		static MemInfo& GetGlobal() { static MemInfo s_Global; return s_Global; }
		inline uintptr_t GetLocNum() const { return reinterpret_cast<uintptr_t>(pLoc); }
		// --setters
		inline void SetAllocation(Size szAlloc, UInt64 unAlloc) { this->szAlloc += szAlloc; this->unAlloc += unAlloc; }
		inline void SetDeallocation(Size szDealloc, UInt64 unDealloc) { this->szAlloc -= szDealloc; this->unAlloc -= unDealloc; }
	};
	inline std::ostream& operator<<(std::ostream& rStream, const MemInfo& rInfo) {
		return rStream <<
			"====<memory_info>====" << std::endl <<
			"address: " << std::hex << rInfo.GetLocNum() << std::dec << std::endl <<
			"total bytes: " << rInfo.szMem << std::endl <<
			"total blocks: " << rInfo.unMem << std::endl <<
			"allocated bytes: " << rInfo.szAlloc << std::endl <<
			"allocated blocks: " << rInfo.unAlloc << std::endl <<
			"====<memory_info>====" << std::endl;
	}
	/// MemLink struct
	struct NWL_API MemLink
	{
	public:
		MemLink* pNext = nullptr;
		Size szBlock = 0;
	public:
		// --getters
		inline MemLink* GetBlock(Size szMem) {
			if (szBlock >= szMem) { this->szBlock -= szMem; return this; }
			MemLink* pBlock = this;
			MemLink* pBlockNext = nullptr;
			while (pBlock != nullptr && pBlockNext != nullptr) {
				if (pBlock = pBlock->pNext) {
					if (pBlockNext = pBlock->pNext) {
						if (pBlockNext->szBlock >= szMem) {
							pBlock->szBlock -= szMem;
							if (pBlock->szBlock == 0) { pBlock->pNext = pBlockNext->pNext; }
							return pBlockNext;
						}
					}
					else { break; }
				}
				else { break; }
			}
			return nullptr;
		}
		template <typename MType> inline operator MType*() { return reinterpret_cast<MType*>(this); }
	};
	/// MemRef struct
	template <typename MType>
	struct NWL_API MemRef
	{
	public:
		MType* pData;
		Size szData;
	public:
		MemRef() : pData(nullptr), szData(0) { }
		MemRef(MemRef<MType>& rCpy): pData(rCpy.pData), szData(rCpy.szData) { }
		MemRef(MType pRef, Size szData = GetAligned(sizeof(MType), alignof(MType))) : pData(pRef), szData(0) { }
		// --operators
		inline operator MType* () { return pData; }
		template<typename VType> inline operator VType* () { return static_cast<VType*>(pData); }
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
			m_Info.szMem = m_Info.unMem = static_cast<UInt64>(szMem);
			m_Info.szAlloc = 0; m_Info.unAlloc = 0;
			m_Info.pLoc = pBlock;
		}
		virtual ~AMemAllocator() { }

		// --getters
		inline Ptr GetDataBeg() { return &m_pBeg[0]; }
		inline Ptr GetDataCur() { return &m_pBeg[m_Info.szAlloc]; }
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
		virtual inline Ptr Alloc(Size szMem, Size szAlign = sizeof(int)) = 0;
		virtual inline void Dealloc(Ptr pBlock, Size szDealloc) = 0;
		virtual inline Ptr Realloc(Ptr pBlock, Size szOld, Size szNew) = 0;
		// --templated_methods
		template<typename MType, typename ... Args>
		inline MType* NewT(Args&& ... Arguments);
		template<typename MType>
		inline MType* NewTArr(UInt64 unAlloc);
		template<typename MType>
		inline void DelT(MType* pBlock);
		template<typename MType>
		inline void DelTArr(MType* pBlock, UInt64 unDealloc);
	protected:
		Byte* m_pBeg;
		MemInfo m_Info;
	};
	template<typename MType, typename ... Args>
	inline MType* AMemAllocator::NewT(Args&& ... Arguments) {
		MType* pBlock = reinterpret_cast<MType*>(Alloc(1 * sizeof(MType), __alignof(MType)));
		new(pBlock) MType(std::forward<Args>(Arguments)...);
		return pBlock;
	}
	template <typename MType>
	inline MType* AMemAllocator::NewTArr(UInt64 unAlloc) {
		return reinterpret_cast<MType*>(Alloc(unAlloc * sizeof(MType), __alignof(MType)));
	}
	template<typename MType>
	inline void AMemAllocator::DelT(MType* pBlock) {
		pBlock->~MType();
		rmAllocator.Dealloc(pBlock, 1 * sizeof(MType));
	}
	template <typename MType>
	inline void AMemAllocator::DelTArr(MType* pBlock, UInt64 unDealloc) {
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
		MemArena(Ptr pBlock = 0, Size szMemory = 0) :
			AMemAllocator(pBlock, szMemory),
			m_FreeList(nullptr) { }
		~MemArena() { }

		// --core_methods
		virtual inline Ptr Alloc(Size szMemory, Size szAlign = sizeof(MemLink)) override;
		virtual inline void Dealloc(Ptr pBlock, Size szDealloc) override;
		virtual inline Ptr Realloc(Ptr pBlock, Size szOld, Size szNew) override;
	private:
		MemLink* m_FreeList;
	};
	// --==<core_methods>==--
	inline Ptr MemArena::Alloc(Size szMemory, Size szAlign) {
		Ptr pBlock = nullptr;
		if (szMemory == 0) { return nullptr; }
		szMemory = GetAligned(szMemory, szAlign);
		if (szMemory < sizeof(MemLink)) { szMemory = sizeof(MemLink); }
		if (m_FreeList != nullptr) {
			if (MemLink* pLink = m_FreeList->GetBlock(szMemory)) {
				pBlock = pLink;
				if (pLink == m_FreeList && m_FreeList->szBlock == 0) { m_FreeList = m_FreeList->pNext; }
			}
			else {
				if (HasEnoughSize(szMemory)) { pBlock = GetDataCur(); }
				else { NWL_ERR("the memory is exhausted!"); }
			}
		}
		else {
			if (HasEnoughSize(szMemory)) { pBlock = GetDataCur(); }
			else { NWL_ERR("the memory is exhausted!"); }
		}
		m_Info.unAlloc++;
		m_Info.szAlloc += szMemory;
		return pBlock;
	}
	inline void MemArena::Dealloc(Ptr pBlock, Size szMemory) {
		if (HasBlock(pBlock)) {
			szMemory = GetAligned(szMemory, sizeof(MemLink));
			if (szMemory < sizeof(MemLink)) { szMemory = sizeof(MemLink); }
			if ((static_cast<Int64>(m_Info.szAlloc) - static_cast<Int64>(szMemory)) < 0) { return; }
			MemLink* pNextFreeList = new(pBlock)MemLink();
			pNextFreeList->pNext = m_FreeList;
			pNextFreeList->szBlock = szMemory;
			m_FreeList = pNextFreeList;
		}
		else { NWL_ERR("the pointer is out of bounds!"); }
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
	/// LinearMemoryAllocator class
	class LinearAllocator : public AMemAllocator
	{
	public:
		LinearAllocator(Ptr pBlock = nullptr, Size szMemory = 0) :
			AMemAllocator(pBlock, szMemory) { }
		~LinearAllocator() { }
		// --core_methods
		virtual inline Ptr Alloc(Size szMemory, Size szAlign = 4) override;
		virtual inline void Dealloc(Ptr pBlock, Size szDealloc) override;
		virtual inline Ptr Realloc(Ptr pBlock, Size szOld, Size szNew) override;
		inline void Clear();
	private:
	};
	// --==<core_methods>==--
	inline Ptr LinearAllocator::Alloc(Size szMemory, Size szAlign) {
		Ptr pBlock = nullptr;
		if (szMemory == 0) { return nullptr; }
		szMemory = GetAligned(szMemory, szAlign);
		if (!HasEnoughSize(szMemory)) { NWL_ERR("The memory is exhausted"); return pBlock; }
		pBlock = GetDataCur();
		m_Info.unAlloc++;
		m_Info.szAlloc += szMemory;
		return pBlock;
	}
	inline void LinearAllocator::Dealloc(Ptr pBlock, Size szMemory) {
		if (pBlock != GetDataCur()) { return; }
		memset(pBlock, 0, szMemory);
		m_Info.unAlloc--;
		m_Info.szAlloc -= szMemory;
	}
	inline Ptr LinearAllocator::Realloc(Ptr pBlock, Size szOld, Size szNew) {
		if (pBlock != GetDataCur()) { return pBlock; }
		Size szCpy = szOld < szNew ? szOld : szNew;
		Ptr pRealloc = Alloc(szNew);
		memcpy(pRealloc, pBlock, szCpy);
		Dealloc(pBlock, szOld);
		return pRealloc;
	}
	inline void LinearAllocator::Clear() {
		memset(GetDataBeg(), 0, GetDataSize());
		m_Info.unAlloc = 0;
		m_Info.szAlloc = 0;
	}
	// --==</core_methods>==--
}

#endif	// NWL_MEMORY_ALLOCATOR_H