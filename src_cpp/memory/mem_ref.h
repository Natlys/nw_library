#ifndef NWL_MEMORY_REF_H
#define NWL_MEMORY_REF_H

#include <nwl_core.hpp>

#include <memory/mem_allocator.h>
#include <memory/mem_sys.h>

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
		RefKeeper(const RefKeeper<MType>& rCpy);
		template<typename VType> RefKeeper(const RefKeeper<VType>& rCpy);
		~RefKeeper() { Reset(); }

		// --getters
		inline MType* GetRef()					{ return (MType*)(m_pRef); }
		inline Size GetSize()					{ return m_szData; }
		inline UInt64* GetCounter()				{ return m_pCounter; }
		template<typename VType> inline VType* GetRef()		{ return static_cast<VType*>(m_pRef); }
		// --setters
		inline void SetRef(MType& rRef, Size szData = GetAligned(sizeof(MType), sizeof(MType)));
		inline void SetRef(const RefKeeper<MType>& rRefKeeper);
		template<typename VType> inline void SetRef(const RefKeeper<VType>& rRefKeeper);
		inline void Reset();
		// --predicates
		inline bool IsValid() { return m_pRef != nullptr && m_pCounter != nullptr && m_szData > 0; }
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
	private:
		mutable MType* m_pRef;
		mutable Size m_szData;
		mutable UInt64* m_pCounter;
	};
	// --constructors_destructors
	template <typename MType>
	RefKeeper<MType>::RefKeeper() : m_pRef(nullptr), m_szData(0), m_pCounter(nullptr) { Reset(); }
	template <typename MType>
	RefKeeper<MType>::RefKeeper(MType& rRef, Size szData) : RefKeeper() { SetRef(rRef, szData); }
	template <typename MType>
	RefKeeper<MType>::RefKeeper(const RefKeeper<MType>& rCpy) : RefKeeper() { SetRef(rCpy); }
	template <typename MType>
	template <typename VType> RefKeeper<MType>::RefKeeper(const RefKeeper<VType>& rCpy) : RefKeeper() { SetRef<VType>(rCpy); }
	// --setters
	template <typename MType>
	inline void RefKeeper<MType>::SetRef(MType& rRef, Size szData) {
		Reset();
		m_pRef = &rRef;
		m_szData = szData;
		m_pCounter = NewT<UInt64>();
		*m_pCounter = 1;
	}
	template <typename MType>
	inline void RefKeeper<MType>::SetRef(const RefKeeper<MType>& rRefKeeper) {
		Reset();
		RefKeeper<MType>& rKeeper = const_cast<RefKeeper<MType>&>(rRefKeeper);
		m_pRef = rKeeper.GetRef<MType>();
		m_szData = rKeeper.GetSize();
		m_pCounter = rKeeper.GetCounter();
		if (m_pCounter != nullptr) { *m_pCounter += 1; }
	}
	template <typename MType>
	template <typename VType> inline void RefKeeper<MType>::SetRef(const RefKeeper<VType>& rRefKeeper) {
		Reset();
		RefKeeper<VType>& rKeeper = const_cast<RefKeeper<VType>&>(rRefKeeper);
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
				MemSys::GetMemory().Dealloc(m_pRef, m_szData);
				MemSys::GetMemory().Dealloc(m_pCounter, sizeof(*m_pCounter));
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
		m_pRef = NewT<VType, Args...>(MemSys::GetMemory(), Arguments...);
		m_szData = GetAligned(sizeof(VType), alignof(VType));
		m_pCounter = NewT<UInt64>(MemSys::GetMemory());
		*m_pCounter = 1;
	}
}

#endif	// NWL_MEMORY_REF_H