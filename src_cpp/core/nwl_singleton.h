#ifndef NWL_SINGLETON_H
#define NWL_SINGLETON_H

#include <nwl_core.hpp>

namespace NWL
{
	class NWL_API AUnique
	{
		//
	};
	/// ASingleton Interface for unique global classes
	template<class SType>
	class NWL_API ASingleton
	{
	protected:
		ASingleton() = default;
		ASingleton(const ASingleton& rCpy) = delete;
	public:
		virtual ~ASingleton() = default;
		// --getters
		static inline SType& Get() { static SType s_instance;  return s_instance; }
		// --operators
		void operator=(const ASingleton& rCpy) = delete;
		Ptr operator new(Size) = delete;
		Ptr operator new[](Size) = delete;
		void operator delete(Ptr) = delete;
		void operator delete[](Ptr) = delete;
	};
}

#endif // NWL_SINGLETON_H