#ifndef NWL_SINGLETON_H
#define NWL_SINGLETON_H
#include <nwl_core.hpp>
namespace NWL
{
	/// abstract singleton for unique global classes
	template<class stype>
	class NWL_API a_singleton
	{
	protected:
		a_singleton() = default;
		a_singleton(const a_singleton& copy) = delete;
	public:
		virtual ~a_singleton() = default;
		// --getters
		static inline stype& Get() { static stype s_instance; return s_instance; }
		// --operators
		void operator=(const a_singleton& copy) = delete;
	};
}

#endif // NWL_SINGLETON_H