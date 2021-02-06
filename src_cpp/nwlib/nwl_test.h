#ifndef NWL_TEST_H
#define NWL_TEST_H

#include <native_world_library.hpp>

namespace NWL
{
	/// Iterator with two links: prev-next iterators
	template<typename ValType>
	class NWL_API Iter2
	{
	public:
		Iter2(Iter2* itPrev = nullptr, Iter2* itNext = nullptr) : m_pRef(nullptr), m_itPrev(itPrev), m_itNext(itNext)
		{
			if (m_itPrev != nullptr) { m_itPrev->m_itNext = this; }
			if (m_itNext != nullptr) { m_itNext->m_itPrev = this; }
		}
		~Iter2()
		{
			if (m_itNext != nullptr) { m_itNext->m_itPrev = m_itPrev; }
			if (m_itPrev != nullptr) { m_itPrev->m_itNext = m_itNext; }
		}

		// --getters
		inline ValType* GetRef() const { return m_pRef; }
		inline Iter2* GetNext() const { return m_itNext; }
		inline Iter2* GetPrev() const { return m_itPrev; }
		// --setters
		inline void SetRef(ValType* pRef) { m_pRef = pRef; }
		inline void SetNext(Iter2* itNext) { if (m_itNext != nullptr) { m_itNext->m_itPrev = nullptr; } m_itNext = itNext; if (itNext != nullptr) { itNext->m_itPrev = this; } }
		inline void SetPrev(Iter2* itPrev) { if (m_itPrev != nullptr) { m_itPrev->m_itNext = nullptr; } m_itPrev = itPrev; if (itPrev != nullptr) { itPrev->m_itNext = this; } }
		// --operators
		inline ValType* operator->() { return m_pRef; }
		inline ValType& operator*() { return *m_pRef; }
		inline bool operator==(Iter2& iter) { return (iter.m_pRef == m_pRef && iter.m_itNext == m_itNext && iter.m_itPrev == m_itPrev); }
		inline bool operator!=(Iter2& iter) { return (iter.m_pRef != m_pRef || iter.m_itNext != m_itNext || iter.m_itPrev != m_itPrev); }
		// --movement
		inline Iter2& operator++() {
			if (m_itNext == nullptr) { NWL_ERR("Out of bounds"); return *this; }

			m_itNext->m_itPrev = m_itPrev;
			if (m_itPrev != nullptr) { m_itPrev->m_itNext = m_itNext; }
			m_itPrev = m_itNext;

			m_itNext = m_itPrev->m_itNext;
			if (m_itNext != nullptr) { m_itNext->m_itPrev = this; }
			m_itPrev->m_itNext = this;
			return *this;
		}
		inline Iter2 operator++(int) {
			if (m_itNext == nullptr) { NWL_ERR("Out of bounds"); return *this; }

			m_itNext->m_itPrev = m_itPrev;
			if (m_itPrev != nullptr) { m_itPrev->m_itNext = m_itNext; }
			m_itPrev = m_itNext;

			m_itNext = m_itPrev->m_itNext;
			if (m_itNext != nullptr) { m_itNext->m_itPrev = this; }
			m_itPrev->m_itNext = this;
			return *this;
		}
		inline Iter2& operator--() {
			if (m_itPrev == nullptr) { NWL_ERR("Out of bounds"); return *this; }

			m_itPrev->m_itNext = m_itNext;
			if (m_itNext != nullptr) { m_itNext->m_itPrev = m_itPrev; }
			m_itNext = m_itPrev;
			m_itPrev = m_itNext->m_itPrev;
			if (m_itPrev != nullptr) { m_itPrev->m_itNext = this; }
			m_itNext->m_itPrev = this;
			return *this;
		}
		inline Iter2 operator--(int) {
			if (m_itPrev == nullptr) { NWL_ERR("Out of bounds"); return *this; }

			m_itPrev->m_itNext = m_itNext;
			if (m_itNext != nullptr) { m_itNext->m_itPrev = m_itPrev; }
			m_itNext = m_itPrev;
			m_itPrev = m_itNext->m_itPrev;
			if (m_itPrev != nullptr) { m_itPrev->m_itNext = this; }
			m_itNext->m_itPrev = this;
			return *this;
		}
		inline void operator+=(UInt32 unSteps) { while (unSteps-- != 0) { operator++(); } }
		inline void operator-=(UInt32 unSteps) { while (unSteps-- != 0) { operator--(); } }
	private:
		ValType* m_pRef;
		Iter2* m_itPrev;
		Iter2* m_itNext;
	};
}
namespace NWL
{
	/// List2 container class
	template<typename ValType>
	class NWL_API List2Test
	{
	public:
		using Iter = Iter2<ValType>;
	public:
		List2Test() :
			m_pAllocator(nullptr), m_itBeg(nullptr), m_itEnd(nullptr), m_unCount(0) {}
		List2Test(AMemAllocator& rAllocator) :
			m_pAllocator(&rAllocator), m_itBeg(nullptr), m_itEnd(nullptr), m_unCount(0)
		{
			m_itBeg = NewT<Iter>(rAllocator, nullptr, nullptr);
			m_itEnd = m_itBeg;
		}
		~List2Test() { Clear(); }

		// --getters
		inline Iter& GetBeg() { return *m_itBeg; }
		inline Iter& GetEnd() { return *m_itEnd; }
		inline UInt64 GetCount() { return m_unCount; }
		// --setters
		// --predicates
		inline bool IsEmpty() { return m_itBeg != m_itEnd; }
		// --operators
		inline Iter& begin() { return *m_itBeg; }
		inline Iter& end() { return *m_itEnd; }
		// --core_methods
		inline void Insert(ValType& rVal, Iter& ritLoc) {
			if (ritLoc.GetRef() != nullptr) { DelT<ValType>(*m_pAllocator, ritLoc.GetRef()); }
			ritLoc.SetRef(NewT<ValType>(*m_pAllocator, rVal));
			if (&ritLoc == m_itEnd) { m_itEnd->SetNext(NewT<Iter>(*m_pAllocator, m_itEnd)); }
			m_unCount++;
		}
		inline void Erase(Iter& ritErase) {
			if (&ritErase == m_itEnd) { NWL_ASSERT(&ritErase != m_itEnd, "Cannot erase the end"); return; }
			DelT<ValType>(*m_pAllocator, ritErase.GetRef());
			if (Iter* pIter = ritErase.GetNext()) {
				pIter->SetPrev(ritErase.GetPrev());
			}
			if (Iter* pIter = ritErase.GetPrev()) {
				pIter->SetNext(ritErase.GetNext());
			}
			if (&ritErase == m_itBeg) { m_itBeg = ritErase.GetNext(); }
			DelT<Iter>(*m_pAllocator, &ritErase);
			m_unCount--;
		}
		inline void Clear() { while (m_itBeg != m_itEnd) { Erase(*m_itBeg); } }
	private:
		AMemAllocator* m_pAllocator;
		Iter* m_itBeg;
		Iter* m_itEnd;
		Size m_unCount;
	};
}
namespace NWL
{
	/// DynamicArray class
	template<typename ValType>
	class NWL_API DArrayTest
	{
	public:
		using Iter = Iter2<ValType>;
	public:
		DArrayTest() : m_itBeg(Iter()), m_itEnd(m_itBeg) { }
		~DArrayTest() { Clear(); }

		// --getters
		inline Iter& GetBeg() { return m_itBeg; }
		inline Iter& GetEnd() { return m_itEnd; }
		// --setters
		// --predicates
		inline bool IsEmpty() { return m_itBeg != m_itEnd; }
		// --operators
		inline Iter& begin() { return m_itBeg; }
		inline Iter& end() { return m_itEnd; }
		// --core_methods
		inline void PushBack(ValType& rVal) {
			m_itEnd.SetRef(NewT<ValType>(rAllocator, rVal));
		}
		inline void Erase(Iter& rIter) {
			for (Iter iter = m_itBeg; iter != m_itEnd; iter.operator++()) {
				if (iter == rIter) {
					break;
				}
			}
			DelT<ValType>(rIter.GetRef());
		}
	private:
		Iter m_itBeg;
		Iter m_itEnd;
	};
}

#endif	// NWL_TEST_H