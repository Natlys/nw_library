#include <nwl_pch.hpp>
#include "mem_allocator.h"

namespace NWL
{
	// --==<MemInfo>==--
	// --setters
	void MemInfo::SetAllocation(Size szData, UInt64 unData) { szAlloc += szData; unAlloc += unData; }
	void MemInfo::SetDeallocation(Size szData, UInt64 unData) { szAlloc -= szData; unAlloc -= unData; }
	// --operators
	std::ostream& MemInfo::operator<<(std::ostream& rStream) const {
		return rStream <<
			"====<memory_info>====" << std::endl <<
			"address: " << std::hex << GetLocNum() << std::dec << std::endl <<
			"total bytes: " << szMem << std::endl <<
			"total blocks: " << unMem << std::endl <<
			"allocated bytes: " << szAlloc << std::endl <<
			"allocated blocks: " << unAlloc << std::endl <<
			"====<memory_info>====" << std::endl;
	}
	std::istream& MemInfo::operator>>(std::istream& rStream) {
		return rStream >>
			szMem >> unMem >>
			szAlloc >> unAlloc >>
			pLoc;
	}
	// --==</MemInfo>==--

	// --==<MemLink>==--
	MemLink* MemLink::GetBlock(Size szMem) {
		if (szBlock >= szMem) { szBlock -= szMem; return this; }
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
	// --==</MemLink>==--
}
namespace NWL
{
	AMemAllocator::AMemAllocator(Ptr pBlock, Size szMemory) :
		m_pBeg(static_cast<Byte*>(pBlock)), m_Info(MemInfo())
	{
		m_Info.szMem = m_Info.unMem = static_cast<UInt64>(szMemory);
		m_Info.szAlloc = 0; m_Info.unAlloc = 0;
		m_Info.pLoc = pBlock;
	}
	AMemAllocator::~AMemAllocator() {}
}
namespace NWL
{
	MemArena::MemArena(Ptr pBlock, Size szMemory) :
		AMemAllocator(pBlock, szMemory),
		m_FreeList(nullptr) { }
	MemArena::~MemArena() {}
	// --==<core_methods>==--
	Ptr MemArena::Alloc(Size szMemory, Size szAlign) {
		Ptr pBlock = nullptr;
		if (szMemory == 0) { return nullptr; }
		szMemory = NWL_ALIGN_FORWARD(szMemory, szAlign);
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
	void MemArena::Dealloc(Ptr pBlock, Size szMemory) {
		if (HasBlock(pBlock)) {
			szMemory = NWL_ALIGN_FORWARD(szMemory, sizeof(MemLink));
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
	Ptr MemArena::Realloc(Ptr pBlock, Size szOld, Size szNew) {
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
	LinearAllocator::LinearAllocator(Ptr pBlock, Size szMemory) :
		AMemAllocator(pBlock, szMemory) { }
	LinearAllocator::~LinearAllocator() { }
	// --==<core_methods>==--
	inline Ptr LinearAllocator::Alloc(Size szMemory, Size szAlign) {
		Ptr pBlock = nullptr;
		if (szMemory == 0) { return nullptr; }
		szMemory = NWL_ALIGN_FORWARD(szMemory, szAlign);
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