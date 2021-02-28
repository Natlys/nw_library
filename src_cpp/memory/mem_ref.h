#ifndef NWL_MEMORY_REF_H
#define NWL_MEMORY_REF_H

#include <nwl_core.hpp>

#include <memory/mem_allocator.h>
#include <memory/mem_sys.h>

namespace NWL
{
	template<typename MType>
	struct NWL_API MemRef : public AMemUser
	{
	public:
		MType mData;
		UInt32 unRefs;
	public:
		template<typename ... Args>
		MemRef(Args&& ... Arguments) : mData(std::forward<Args>(Argument)) {}
		~MemRef();
	};
	/// RefKeeper class
	/// Description:
	/// -- Smart "shared" pointer in nw implementation
	/// -- Allocates object due to given allocator
	/// -- The reference gets deleted if there is no any other RefKeepers for it
	/// Interface:
	/// -> Create RefKeeper -> MakeRef with particular allocator -> SetRef for other keepers -> use as a pointer
	template <typename MType>
	class NWL_API RefKeeper : public AMemUser
	{
	public:
		RefKeeper();
		RefKeeper(MType& rRef);
		RefKeeper(const RefKeeper<MType>& rCpy);
		template<typename VType> RefKeeper(const RefKeeper<VType>& rCpy);
		~RefKeeper() { Reset(); }
		// --getters
		inline MType* GetRef()		{ return static_cast<MType*>(m_pRef); }
		inline UInt64* GetCounter()	{ return m_pCounter; }
		template<typename VType>
		inline VType* GetRef()		{ return static_cast<VType*>(m_pRef); }
		// --setters
		void SetRef(MType& rRef);
		void SetRef(const RefKeeper<MType>& rRefKeeper);
		template<typename VType> void SetRef(const RefKeeper<VType>& rRefKeeper);
		void Reset();
		// --predicates
		inline bool IsValid() { return m_pRef != nullptr && m_pCounter != nullptr; }
		// --operators
		inline operator bool() { return m_pRef != nullptr; }
		inline MType* operator->()	{ return (m_pRef); }
		inline MType& operator*()	{ return *(m_pRef); }
		inline operator MType* ()	{ return static_cast<MType*>(m_pRef); }
		inline operator MType& ()	{ return static_cast<MType&>(*m_pRef); }
		inline RefKeeper<MType>& operator=(const RefKeeper<MType>& rCpy) { SetRef(rCpy); return *this; }
		template<typename VType> operator VType*() { return static_cast<VType*>(m_pRef); }
		template<typename VType> operator RefKeeper<VType>() { RefKeeper<VType> memRefKeeper(*this); return memRefKeeper; }
		// --core_methods
		template <typename VType, typename ... Args> void MakeRef(Args&& ... Arguments);
	private:
		mutable MType* m_pRef;
		mutable UInt64* m_pCounter;
	};
	// --constructors_destructors
	template <typename MType>
	RefKeeper<MType>::RefKeeper() : m_pRef(nullptr), m_pCounter(nullptr) { Reset(); }
	template <typename MType>
	RefKeeper<MType>::RefKeeper(MType& rRef) : RefKeeper() { SetRef(rRef); }
	template <typename MType>
	RefKeeper<MType>::RefKeeper(const RefKeeper<MType>& rCpy) : RefKeeper() { SetRef(rCpy); }
	template <typename MType>
	template <typename VType> RefKeeper<MType>::RefKeeper(const RefKeeper<VType>& rCpy) : RefKeeper() { SetRef<VType>(rCpy); }
	// --setters
	template <typename MType>
	void RefKeeper<MType>::SetRef(MType& rRef) {
		Reset();
		m_pRef = &rRef;
		m_pCounter = MemSys::NewT<UInt64>();
		*m_pCounter = 1;
	}
	template <typename MType>
	void RefKeeper<MType>::SetRef(const RefKeeper<MType>& rRefKeeper) {
		Reset();
		RefKeeper<MType>& rKeeper = const_cast<RefKeeper<MType>&>(rRefKeeper);
		m_pRef = rKeeper.GetRef<MType>();
		m_pCounter = rKeeper.GetCounter();
		if (m_pCounter != nullptr) { *m_pCounter += 1; }
	}
	template <typename MType>
	template <typename VType> void RefKeeper<MType>::SetRef(const RefKeeper<VType>& rRefKeeper) {
		Reset();
		RefKeeper<VType>& rKeeper = const_cast<RefKeeper<VType>&>(rRefKeeper);
		m_pRef = rKeeper.GetRef<MType>();
		m_pCounter = rKeeper.GetCounter();
		if (m_pCounter != nullptr) { *m_pCounter += 1; }
	}
	template <typename MType>
	void RefKeeper<MType>::Reset() {
		if (m_pCounter != nullptr) {
			*m_pCounter -= 1;
			if (*m_pCounter == 0) {
				delete m_pRef;
				m_pRef = nullptr;
				MemSys::Dealloc(m_pCounter, sizeof(*m_pCounter));
				m_pCounter = nullptr;
			}
		}
		m_pRef = nullptr;
		m_pCounter = nullptr;
	}
	// --core_methods
	template <typename MType>
	template <typename VType, typename ... Args> void RefKeeper<MType>::MakeRef(Args&& ... Arguments) {
		Reset();
		m_pRef = new VType(std::forward<Args>(Arguments)...);
		m_pCounter = MemSys::NewT<UInt64>();
		*m_pCounter = 1;
	}
}

#endif	// NWL_MEMORY_REF_H