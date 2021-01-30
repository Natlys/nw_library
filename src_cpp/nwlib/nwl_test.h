#ifndef NWL_TEST_H
#define NWL_TEST_H

#include <native_world_library.hpp>

namespace NWL
{
	/// Iterator with two links: prev-next iterators
	template<typename ValType>
	class NWL_API Iter2Link
	{
	public:
		Iter2Link(Iter2Link* itPrev = nullptr, Iter2Link* itNext = nullptr) : m_pRef(nullptr), m_itPrev(itPrev), m_itNext(itNext)
		{
			if (m_itPrev != nullptr) { m_itPrev->m_itNext = this; }
			if (m_itNext != nullptr) { m_itNext->m_itPrev = this; }
		}
		~Iter2Link()
		{
			if (m_itNext != nullptr) { m_itNext->m_itPrev = m_itPrev; }
			if (m_itPrev != nullptr) { m_itPrev->m_itNext = m_itNext; }
		}

		// --getters
		inline ValType* GetRef() const { return m_pRef; }
		inline Iter2Link* GetNext() const { return m_itNext; }
		inline Iter2Link* GetPrev() const { return m_itPrev; }
		// --setters
		inline void SetRef(ValType* pRef) { m_pRef = pRef; }
		inline void SetNext(Iter2Link* itNext) { if (m_itNext != nullptr) { m_itNext->m_itPrev = nullptr; } m_itNext = itNext; if (itNext != nullptr) { itNext->m_itPrev = this; } }
		inline void SetPrev(Iter2Link* itPrev) { if (m_itPrev != nullptr) { m_itPrev->m_itNext = nullptr; } m_itPrev = itPrev; if (itPrev != nullptr) { itPrev->m_itNext = this; } }
		// --operators
		inline ValType* operator->() { return m_pRef; }
		inline ValType& operator*() { return *m_pRef; }
		inline bool operator==(Iter2Link& iter) { return (iter.m_pRef == m_pRef && iter.m_itNext == m_itNext && iter.m_itPrev == m_itPrev); }
		inline bool operator!=(Iter2Link& iter) { return (iter.m_pRef != m_pRef || iter.m_itNext != m_itNext || iter.m_itPrev != m_itPrev); }
		// --movement
		inline void operator++() {
			if (m_itNext == nullptr) { NWL_ERR("Out of bounds"); return; }

			m_itNext->m_itPrev = m_itPrev;
			if (m_itPrev != nullptr) { m_itPrev->m_itNext = m_itNext; }
			m_itPrev = m_itNext;

			m_itNext = m_itPrev->m_itNext;
			if (m_itNext != nullptr) { m_itNext->m_itPrev = this; }
			m_itPrev->m_itNext = this;
		}
		inline void operator--() {
			if (m_itPrev == nullptr) { NWL_ERR("Out of bounds"); return; }

			m_itPrev->m_itNext = m_itNext;
			if (m_itNext != nullptr) { m_itNext->m_itPrev = m_itPrev; }
			m_itNext = m_itPrev;
			m_itPrev = m_itNext->m_itPrev;
			if (m_itPrev != nullptr) { m_itPrev->m_itNext = this; }
			m_itNext->m_itPrev = this;
		}
		inline void operator+=(UInt32 unSteps) { while (unSteps-- != 0) { operator++(); } }
		inline void operator-=(UInt32 unSteps) { while (unSteps-- != 0) { operator--(); } }
	private:
		ValType* m_pRef;
		Iter2Link* m_itPrev;
		Iter2Link* m_itNext;
	};

	/// List2Link container class
	template<typename ValType, AMemAllocator& rAllocator>
	class NWL_API List2Link
	{
		using Iter = Iter2Link<ValType>;
	public:
		List2Link() : m_itBeg(Iter()), m_itEnd(m_itBeg) { }
		~List2Link() { while (m_itBeg != m_itEnd) { ; } }

		// --getters
		inline Iter& GetBeg() { return m_itBeg; }
		inline Iter& GetEnd() { return m_itEnd; }
		// --setters
		// --predicates
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