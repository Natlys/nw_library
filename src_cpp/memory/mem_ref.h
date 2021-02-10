#ifndef NWL_MEMORY_REF_H
#define NWL_MEMORY_REF_H

#include <nwl_core.hpp>

#include <memory/mem_allocator.h>
#include <memory/mem_sys.h>

#if false
namespace NWL
{
	/// MemoryReference struct for RefKeeper class
	/// Description:
	/// -- Set of data for object handling in a memory chunk
	template<typename MType>
	struct MemRef
	{
	public:

	public:
		MemRef() {}
		MemRef(const MemRef<MType>& rCpy) = delete;
		~MemRef();
		// --predicates
		inline bool IsValid() { return pAllocator != nullptr && pRef != nullptr && szData >= 1 && unRefs > 0; }
		// --operators
		inline void operator=(const MemRef<MType>& rCpy);
		inline MType* operator*() { return pRef; }
		inline MType& operator->() { return *pRef; }
		inline operator MType*() { return static_cast<MType*>(pRef); }
		template<typename VType> inline operator VType* () { return static_cast<VType*>(pRef); }
		template<typename VType> inline operator MemRef<VType>();
	};
	template<typename MType>
	MemRef<MType>::~MemRef<MType>() {
		if (pRef != nullptr && pAllocator != nullptr && szData != 0) {
			if (unRefs == 0) { pRef->~MType(); pAllocator->Dealloc(pRef, szData); }
		}
	}
	template<typename MType>
	inline void MemRef<MType>::operator=(const MemRef<MType>& rCpy) {
		rCpy.pRef = pRef;
		rCpy.szData = szData;
		rCpy.pAllocator = pAllocator;
		rCpy.unRefs = ++unRefs;
	}
	template<typename MType>
	template<typename VType> inline MemRef<MType>::operator MemRef<VType>() {
		MemRef<VType> memRef;
		memRef.pAllocator = pAllocator;
		memRef.pRef = static_cast<VType*>(pRef);
		memRef.szData = szData;
		memRef.unRefs = ++unRefs;
		return memRef;
	}
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
		explicit RefOwner(const RefOwner<MType>& rCpy) = delete;
		~RefOwner() { Reset(); }

		// --getters
		inline MType* GetRef() { return m_Ref.pRef; }
		template<typename VType>
		inline VType* GetRef() { return static_cast<VType*>(m_pRef->pRef); }
		inline Size GetSize()		const { return m_Ref.szData; }
		// --setters
		inline void SetRef(MType& rRef, Size szData = GetAligned(sizeof(MType), sizeof(MType)));
		inline void SetRef(AMemAllocator& rAllocator, MType& rRef, Size szData = GetAligned(sizeof(MType), sizeof(MType)));
		inline void Reset();
		// --predicates
		inline bool IsValid() { return m_Ref.IsValid(); }
		// --operators
		inline void operator=(const RefOwner<MType>& rCpy) = delete;
		inline MType* operator->() { return m_Ref; }
		inline MType& operator*() { return *m_Ref; }
		inline operator MType*() { return static_cast<MType*>(m_Ref); }
		template<typename VType> inline operator MType*() { return static_cast<VType*>(m_Ref); }
		template<typename VType> inline operator RefOwner<VType>();
		// --core_methods
		template <typename VType, typename ... Args>
		inline void MakeRef(Args& ... Arguments);
		template <typename VType, typename ... Args>
		inline void MakeRef(AMemAllocator& rAllocator, Args& ... Arguments);
	private:
		AMemAllocator* pAllocator = nullptr;
		MType* pRef = nullptr;
		Size szData = GetAligned(sizeof(MType), sizeof(MType));
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
	// --operators
	template<typename MType>
	template<typename VType> inline RefOwner<MType>::operator RefOwner<VType>() {
		RefOwner<VType> memRefOwner;
		memRefOwner.m_Ref = m_Ref;
		Reset();
		return memRefOwner;
	}
	// --core_methods
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
#endif
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
		RefKeeper();
		RefKeeper(MType& rRef, Size szData = GetAligned(sizeof(MType), sizeof(MType)));
		RefKeeper(AMemAllocator& rAllocator, MType& rRef, Size szData = GetAligned(sizeof(MType), sizeof(MType)));
		RefKeeper(const RefKeeper<MType>& rCpy);
		template<typename VType> RefKeeper(const RefKeeper<VType>& rCpy);
		~RefKeeper() { Reset(); }

		// --getters
		inline AMemAllocator* GetAllocator()	{ return m_pAllocator; }
		inline MType* GetRef()					{ return (MType*)(m_pRef); }
		inline Size GetSize()					{ return m_szData; }
		inline UInt64* GetCounter()				{ return m_pCounter; }
		template<typename VType> inline VType* GetRef()		{ return (VType*)(m_pRef); }
		// --setters
		inline void SetRef(MType& rRef, Size szData = GetAligned(sizeof(MType), sizeof(MType)));
		inline void SetRef(AMemAllocator& rAllocator, MType& rRef, Size szData = GetAligned(sizeof(MType), sizeof(MType)));
		inline void SetRef(const RefKeeper<MType>& rRefKeeper);
		template<typename VType> inline void SetRef(const RefKeeper<VType>& rRefKeeper);
		inline void Reset();
		// --predicates
		inline bool IsValid() { return m_pRef != nullptr && m_pCounter != nullptr && m_pAllocator != nullptr && m_szData > 0; }
		// --operators
		inline MType* operator->() { return (m_pRef); }
		inline MType& operator*() { return *(m_pRef); }
		inline RefKeeper<MType>& operator=(const RefKeeper<MType>& rCpy) { SetRef(rCpy); return *this; }
		inline operator MType* () { return static_cast<MType*>(m_pRef); }
		template<typename VType> inline operator RefKeeper<VType>() { RefKeeper<VType> memRefKeeper(*this); return memRefKeeper; }
		template<typename VType> inline operator VType*() { return static_cast<VType*>(m_pRef); }
		// --core_methods
		template <typename VType, typename ... Args>
		inline void MakeRef(Args ... Arguments);
		template <typename VType, typename ... Args>
		inline void MakeRef(AMemAllocator& rAllocator, Args ... Arguments);
	private:
		mutable AMemAllocator* m_pAllocator;
		mutable MType* m_pRef;
		mutable Size m_szData;
		mutable UInt64* m_pCounter;
	};
	// --constructors_destructors
	template <typename MType>
	RefKeeper<MType>::RefKeeper() : m_pAllocator(nullptr), m_pRef(nullptr), m_szData(0), m_pCounter(nullptr) { Reset(); }
	template <typename MType>
	RefKeeper<MType>::RefKeeper(MType& rRef, Size szData) : RefKeeper() { SetRef(rRef, szData); }
	template <typename MType>
	RefKeeper<MType>::RefKeeper(AMemAllocator& rAllocator, MType& rRef, Size szData) : RefKeeper() { SetRef(rAllocator, rRef, szData); }
	template <typename MType>
	RefKeeper<MType>::RefKeeper(const RefKeeper<MType>& rCpy) : RefKeeper() { SetRef(rCpy); }
	template <typename MType>
	template <typename VType> RefKeeper<MType>::RefKeeper(const RefKeeper<VType>& rCpy) : RefKeeper() { SetRef<VType>(rCpy); }
	// --setters
	template <typename MType>
	inline void RefKeeper<MType>::SetRef(MType& rRef, Size szData) {
		Reset();
		m_pAllocator = &MemSys::GetMemory();
		m_pRef = &rRef;
		m_szData = szData;
		m_pCounter = NewT<UInt64>();
		*m_pCounter = 1;
	}
	template <typename MType>
	inline void RefKeeper<MType>::SetRef(AMemAllocator& rAllocator, MType& rRef, Size szData) {
		Reset();
		m_pAllocator = &rAllocator;
		m_pRef = &rRef;
		m_szData = szData;
		m_pCounter = NewT<UInt64>(rAllocator);
		*m_pCounter = 1;
	}
	template <typename MType>
	inline void RefKeeper<MType>::SetRef(const RefKeeper<MType>& rRefKeeper) {
		Reset();
		RefKeeper<MType>& rKeeper = const_cast<RefKeeper<MType>&>(rRefKeeper);
		m_pAllocator = rKeeper.GetAllocator();
		m_pRef = rKeeper.GetRef<MType>();
		m_szData = rKeeper.GetSize();
		m_pCounter = rKeeper.GetCounter();
		if (m_pCounter != nullptr) { *m_pCounter += 1; }
	}
	template <typename MType>
	template <typename VType> inline void RefKeeper<MType>::SetRef(const RefKeeper<VType>& rRefKeeper) {
		Reset();
		RefKeeper<VType>& rKeeper = const_cast<RefKeeper<VType>&>(rRefKeeper);
		m_pAllocator = rKeeper.GetAllocator();
		m_pRef = rKeeper.GetRef<MType>();
		m_szData = rKeeper.GetSize();
		m_pCounter = rKeeper.GetCounter();
		if (m_pCounter != nullptr) { *m_pCounter += 1; }
	}
	template <typename MType>
	inline void RefKeeper<MType>::Reset() {
		if (m_pCounter != nullptr) {
			*m_pCounter -= 1;
			if (*m_pCounter == 0) {
				m_pRef->~MType();
				m_pAllocator->Dealloc(m_pRef, m_szData);
				m_pAllocator->Dealloc(m_pCounter, sizeof(*m_pCounter));
				m_pAllocator = nullptr;
				m_pRef = nullptr;
				m_szData = 0;
				m_pCounter = nullptr;
			}
		}
	}
	// --core_methods
	template <typename MType>
	template <typename VType, typename ... Args>
	inline void RefKeeper<MType>::MakeRef(Args ... Arguments) {
		Reset();
		m_pAllocator = &MemSys::GetMemory();
		m_pRef = NewT<VType>(MemSys::GetMemory(), std::forward<Args>(Arguments)...);
		m_szData = GetAligned(sizeof(VType), alignof(VType));
		m_pCounter = NewT<UInt64>(MemSys::GetMemory());
		*m_pCounter = 1;
	}
	template <typename MType>
	template <typename VType, typename ... Args>
	inline void RefKeeper<MType>::MakeRef(AMemAllocator& rAllocator, Args ... Arguments) {
		Reset();
		m_pAllocator = &rAllocator;
		m_pRef = NewT<VType>(rAllocator, std::forward<Args>(Arguments)...);
		m_szData = GetAligned(sizeof(VType), alignof(VType));
		m_pCounter = NewT<UInt64>(rAllocator);
		*m_pCounter = 1;
	}
}

#endif	// NWL_MEMORY_REF_H