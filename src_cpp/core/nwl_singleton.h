#ifndef NWL_SINGLETON_H
#define NWL_SINGLETON_H

#include <nwl_core.hpp>

namespace NWL
{
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
	};
}

#endif // NWL_SINGLETON_H