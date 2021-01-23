#ifndef NWL_SINGLETON_H
#define NWL_SINGLETON_H

#include <nwl_core.hpp>

namespace NWL
{
	/// ASingleton Interface for unique global classes
	template<class SType>
	class NWL_API ASingleton
	{
	public:
		ASingleton(const ASingleton& rCpy) = delete;
		virtual ~ASingleton() = default;
		// --getters
		static inline SType& Get() { static SType s_instance;  return s_instance; }
		
		void operator =(ASingleton& rCpy) = delete;
		void operator =(const ASingleton& rCpy) = delete;
	protected:
		ASingleton() = default;
	};
}

#endif // NWL_SINGLETON_H