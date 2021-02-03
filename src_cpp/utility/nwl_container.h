#ifndef NWL_CONTAINER_H
#define NWL_CONTAINER_H

#include <nwl_core.hpp>
#include <nwl_memory.hpp>

namespace NWL
{
	template <typename ValType>
	using DArray = std::vector<ValType>;
	template <typename ValType>
	using DStack = std::stack<ValType>;
	template <typename ValType>
	using List2 = std::list<ValType>;
	template <typename KeyType, typename ValType>
	using HashMap = std::unordered_map<KeyType, ValType>;
}

namespace NWL
{
	/// Pair struct
	template<typename Type1, typename Type2>
	struct NWL_API Pair
	{
	public:
		Type1 First;
		Type2 Second;
	public:
		Pair(Type1 val1, Type2 val2) :
			Firts(val1), Second(val2) { }
		Pair(const Pair<Type1, Type2>& rCpy) :
			Firts(rCpy.First), Second(rCpy.Second) { }
	};
}

namespace NWL
{
	/// StaticArray class
	template <typename ValType, UInt64 unSize>
	class NWL_API SArray
	{
	public:
		// --getters
		inline const UInt64 GetSize() const { return unSize; }
		// --setters
		// --operators
		inline ValType& operator[](UInt64 unIdx) { return m_Data[unIdx]; }
		inline const ValType& operator[](UInt64 unIdx) const { return m_Data[unIdx]; }
		// --core_methods
	private:
		ValType m_Data[unSize];
	};
}
#if false
namespace NWL
{
	/// DynamicArray class
	template <typename ValType>
	class NWL_API DArray
	{
	public:
		DArray(const DArray& rCpy) { }
		~DArray() { Clear(); }

		// --getters
		inline const UInt64 GetCount() const { return m_unCount; }
		inline const UInt64 GetSlots() const { return m_unSlots; }
		// --setters
		inline void SetSize(UInt64 unSize) {
			if (m_unSlots > unSize) {
				DelTArr<ValType>(&m_Data[0], m_unSlots);
			}
			else if (m_unSlots < unSize) {
				DelTArr<ValType>(&m_Data[0], m_unSlots);
			}
			m_unSlots = unSlots;
		}
		inline void Push(UInt64 unIdx, ValType& rCpy) {
			if (unIdx > m_unSlots) { NWL_ERR("there is not enough space"); return; }
		}
		inline void PushBack(ValType& rCpy) {
			if (m_unCount >= m_unSlots) { SetSlots(m_unSlots * 2); }
			NewPlaceT<ValType>(&m_Data[m_unCount++], rCpy);
		}

		// --core_methods
		inline void Clear() { DelTArr<ValType>(m_Data, m_unSize); m_unCount = 0; m_unSize = 0; }

		// Operators
		inline DArray& operator=(const DArray& rCpy) { }
		inline DArray& operator=(DArray&& rCpy) { }
		inline ValType& operator[](UInt64 unIdx) { return m_Data[unIdx]; }
	private:
		ValType* m_Data;
		UInt64 m_unCount;
		UInt64 m_unSize;
	};
}
#endif

#endif	// NWL_CONTAINER_H