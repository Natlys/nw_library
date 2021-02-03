#ifndef NWL_MEMORY_REF_H
#define NWL_MEMORY_REF_H

#include <nwl_core.hpp>

#include <memory/mem_allocator.h>
#include <memory/mem_sys.h>

namespace NWL
{
	/// MemoryReference struct for RefKeeper class
	/// Description:
	/// -- Set of data for object handling in a memory chunk
	template<typename MType>
	struct MemRef
	{
	public:
		AMemAllocator* pAllocator = nullptr;
		Size szData = GetAligned(sizeof(MType), sizeof(MType));
		MType* pRef = nullptr;
		UInt16 unRefs = 0;
	public:
		MemRef() {}
		~MemRef() {
			if (pRef != nullptr && pAllocator != nullptr && szData != 0 && unRefs == 0) {
				pRef->~MType(); pAllocator->Dealloc(pRef, szData);
			}
		}
		// --predicates
		inline bool IsValid() { return pAllocator != nullptr && pRef != nullptr && szData >= 1 && unRefs > 0; }
	};
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
		RefOwner() : m_Ref(MemRef<MType>()) {}
		RefOwner(MType& rRef, Size szData = GetAligned(sizeof(MType), sizeof(MType)));
		RefOwner(AMemAllocator& rAllocator, MType& rRef, Size szData = GetAligned(sizeof(MType), sizeof(MType)));
		explicit RefOwner(const RefOwner& rCpy) = delete;
		~RefOwner() { Reset(); }

		// --getters
		inline MType* GetRef()		{ return m_Ref.pRef; }
		template<typename VType>
		inline VType* GetRef()		{ return static_cast<VType*>(m_pRef->pRef); }
		inline Size GetSize()		const { return m_Ref.szData; }
		// --setters
		inline void SetRef(MType& rRef, Size szData = GetAligned(sizeof(MType), sizeof(MType)));
		inline void SetRef(AMemAllocator& rAllocator, MType& rRef, Size szData = GetAligned(sizeof(MType), sizeof(MType)));
		inline void Reset();
		// --predicates
		inline bool IsValid() { return m_Ref.IsValid(); }
		// --core_methods
		template <typename VType, typename ... Args>
		inline void MakeRef(Args& ... Arguments);
		template <typename VType, typename ... Args>
		inline void MakeRef(AMemAllocator& rAllocator, Args& ... Arguments);
		// --operators
		inline MType* operator->() { return m_Ref.pRef; }
		inline MType& operator*() { return *m_Ref.pRef; }
		inline void operator=(const RefOwner& rCpy) = delete;
	private:
		MemRef<MType> m_Ref;
	};
	// --constructors_destructors
	template <typename MType>
	RefOwner<MType>::RefOwner(AMemAllocator& rAllocator, MType& rRef, Size szData) :
		m_Ref(MemRef<MType>()), { SetRef(rAllocator, rRef, szData;) }
		template <typename MType>
	RefOwner<MType>::RefOwner(MType& rRef, Size szData) :
		m_Ref(MemRef<MType>()), { SetRef(MemSys::GetMemory(), rRef, szData;) }
	// --setters
	template <typename MType>
	inline void RefOwner<MType>::SetRef(MType& rRef, Size szData) {
		Reset();
		m_Ref.pAllocator = &MemSys::GetMemory();
		m_Ref.szData = szData;
		m_Ref.pRef = &rRef;
		m_Ref.unRefs = 1;
	}
	template <typename MType>
	inline void RefOwner<MType>::SetRef(AMemAllocator& rAllocator, MType& rRef, Size szData) {
		Reset();
		m_Ref.pAllocator = &rAllocator;
		m_Ref.szData = szData;
		m_Ref.pRef = &rRef;
		m_Ref.unRefs = 1;
	}
	template <typename MType>
	inline void RefOwner<MType>::Reset() {
		m_Ref.unRefs = 0;
		m_Ref = MemRef<MType>();
	}
	template <typename MType>
	template<typename VType, typename ... Args>
	inline void RefOwner<MType>::MakeRef(Args& ... Arguments) {
		Reset();
		m_Ref.pAllocator = &MemSys::GetMemory();
		m_Ref.szData = GetAligned(sizeof(VType), alignof(VType));
		m_Ref.pRef = NewT<VType>(rAllocator, std::forward<Args>(Arguments)...);
		m_Ref.unRefs = 1;
	}
	template <typename MType>
	template<typename VType, typename ... Args>
	inline void RefOwner<MType>::MakeRef(AMemAllocator& rAllocator, Args& ... Arguments) {
		Reset();
		m_Ref.pAllocator = &rAllocator;
		m_Ref.szData = GetAligned(sizeof(VType), alignof(VType));
		m_Ref.pRef = NewT<VType>(rAllocator, std::forward<Args>(Arguments)...);
		m_Ref.unRefs = 1;
	}
}
namespace NWL
{
	/// RefKeeper class
	/// Description:
	/// -- Smart "shared" pointer in nw implementation
	/// -- Allocates object due to given allocator
	/// -- The reference gets deleted if there is no any other RefKeepers for it
	/// Interface:
	/// -> Create RefKeeper -> MakeRef with particular allocator -> SetRef for other keepers -> use as a pointer
	template <typename MType>
	class NWL_API RefKeeper
	{
	public:
		RefKeeper() : m_pRef(nullptr) {}
		RefKeeper(MType& rRef, Size szData = GetAligned(sizeof(MType), sizeof(MType)));
		RefKeeper(AMemAllocator& rAllocator, MType& rRef, Size szData = GetAligned(sizeof(MType), sizeof(MType)));
		RefKeeper(const RefKeeper& rCpy) : m_pRef(rCpy.m_pRef) { if (m_pRef != nullptr) { m_pRef->unRefs++; } }
		~RefKeeper() { Reset(); }

		// --getters
		inline MType* GetRef() { return m_pRef->pRef; }
		template<typename VType>
		inline VType* GetRef() { return static_cast<VType*>(m_pRef->pRef); }
		inline Size GetSize()		const { return m_pRef->szData; }
		inline UInt16 GetCount()	const { return m_pRef->unRefs; }
		// --setters
		inline void SetRef(RefKeeper<MType>& rRefKeeper);
		inline void SetRef(MType& rRef, Size szData = GetAligned(sizeof(MType), sizeof(MType)));
		inline void SetRef(AMemAllocator& rAllocator, MType& rRef, Size szData = GetAligned(sizeof(MType), sizeof(MType)));
		inline void Reset();
		// --predicates
		inline bool IsValid() { if (m_pRef != nullptr) { return m_pRef->IsValid(); } else { return false; } }
		// --core_methods
		template <typename VType, typename ... Args>
		inline void MakeRef(Args ... Arguments);
		template <typename VType, typename ... Args>
		inline void MakeRef(AMemAllocator& rAllocator, Args ... Arguments);
		// --operators
		inline MType* operator->() { return (m_pRef->pRef); }
		inline MType& operator*() { return *(m_pRef->pRef); }
		inline RefKeeper& operator=(RefKeeper& rCpy) { SetRef(rCpy); return *this; }
		inline operator MType* () { return m_pRef->pRef; }
	private:
		mutable MemRef<MType>* m_pRef;
	};
	// --constructors_destructors
	template <typename MType>
	RefKeeper<MType>::RefKeeper(MType& rRef, Size szData) :
		m_pRef(nullptr) {
		SetRef(rRef, szData);
	}
	template <typename MType>
	RefKeeper<MType>::RefKeeper(AMemAllocator& rAllocator, MType& rRef, Size szData) :
		m_pRef(nullptr) { SetRef(rAllocator, rRef, szData); }
	// --setters
	template <typename MType>
	inline void RefKeeper<MType>::SetRef(MType& rRef, Size szData) {
		Reset();
		m_pRef = NewT<MemRef<MType>>(MemSys::GetMemory());
		m_pRef->pAllocator = &MemSys::GetMemory();
		m_pRef->pRef = &rRef;
		m_pRef->szData = szData;
		m_pRef->unRefs = 1;
	}
	template <typename MType>
	inline void RefKeeper<MType>::SetRef(AMemAllocator& rAllocator, MType& rRef, Size szData) {
		Reset();
		m_pRef = NewT<MemRef<MType>>(rAllocator);
		m_pRef->pAllocator = &rAllocator;
		m_pRef->pRef = &rRef;
		m_pRef->szData = szData;
		m_pRef->unRefs = 1;
	}
	template <typename MType>
	inline void RefKeeper<MType>::SetRef(RefKeeper<MType>& rRefKeeper) {
		Reset();
		m_pRef = rRefKeeper.m_pRef;
		if (m_pRef != nullptr) { m_pRef->unRefs += 1; }
	}
	template <typename MType>
	inline void RefKeeper<MType>::Reset() {
		if (m_pRef != nullptr) {
			m_pRef->unRefs--;
			if (m_pRef->unRefs == 0) {
				DelT<MemRef<MType>>(*m_pRef->pAllocator, m_pRef);
				m_pRef = nullptr;
			}
		}
	}
	// --core_methods
	template <typename MType>
	template <typename VType, typename ... Args>
	inline void RefKeeper<MType>::MakeRef(Args ... Arguments) {
		Reset();
		m_pRef = NewT<MemRef<MType>>();
		m_pRef->pAllocator = &MemSys::GetMemory();
		m_pRef->pRef = NewT<VType>(Arguments...);
		m_pRef->szData = GetAligned(sizeof(VType), alignof(VType));
		m_pRef->unRefs = 1;
	}
	template <typename MType>
	template <typename VType, typename ... Args>
	inline void RefKeeper<MType>::MakeRef(AMemAllocator& rAllocator, Args ... Arguments) {
		Reset();
		m_pRef = NewT<MemRef<MType>>(rAllocator);
		m_pRef->pAllocator = &rAllocator;
		m_pRef->pRef = NewT<VType>(rAllocator, Arguments...);
		m_pRef->szData = GetAligned(sizeof(VType), alignof(VType));
		m_pRef->unRefs = 1;
	}
}

#endif	// NWL_MEMORY_REF_H