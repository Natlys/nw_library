#ifndef NWL_CONTAINER_H
#define NWL_CONTAINER_H

#include <nwl_core.hpp>

#include <array>
#include <vector>
#include <stack>
#include <list>
#include <map>
#include <unordered_map>

namespace NWL
{
	template <typename ValType, Size szCapacity>
	using SArray = std::array<ValType, szCapacity>;
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
#if false
	template <typename Type, int size>
	class NW_API SArray
	{
	public:
		SArray()
		{
			//
		}
		SArray(UInt16 size)
		{
			//
		}
		SArray(SArray& saCopied)
		{
			//
		}
		SArray(SArray&& saMoved)
		{
			//
		}
		~SArray() {}
		
		// Getters
		inline const UInt32 GetCount() const
		{
			return m_unCount;
		}
		inline const UInt32 GetSlots() const
		{
			return m_unSlots;
		}
		// Setters
		inline void SetCount()
		{
			//
		}
		
		// Interface Methods
		inline void PushBack(Type)
		{
			//
		}
		inline void Clear()
		{
			//
		}

		// Operators
		SArray& operator=(SArray& saCopied)
		{
		}
		SArray& operator=(SArray&& saMoved)
		{
		}
		Type& operator[](int index)
		{
		}
		const Type& operator[](int index) const
		{
		}
	private:
		Type* m_tElems;
		UInt m_unCount;
		UInt m_unSlots;
	};
	template <typename Type>
	class NW_API DArray
	{
	public:
		DArray()
		{
			//
		}
		explicit DArray(UInt16 size)
		{
			//
		}
		DArray(DArray& daCopied)
		{
			//
		}
		DArray(DArray&& daMoved)
		{
			//
		}
		~DArray()
		{
			//
		}

		// Getters
		inline const UInt32 GetCount() const
		{
			return m_unCount;
		}
		inline const UInt32 GetSlots() const
		{
			return m_unSlots;
		}
		// Setters
		inline void SetCount()
		{
			//
		}
		inline void SetSlots()
		{
			//
		}

		// Interface Methods
		inline void PushBack(Type)
		{
			//
		}
		inline void Clear()
		{
			//
		}

		// Operators
		DArray& operator=(DArray& daCopied)
		{
		}
		DArray& operator=(DArray&& daMoved)
		{
		}
		DArray& operator[](int index)
		{
		}
	private:
		Type* m_tElems;
		UInt32 m_unCount;
		UInt32 m_unSlots;
	};
#endif
}
#endif // NWL_CONTAINER_H