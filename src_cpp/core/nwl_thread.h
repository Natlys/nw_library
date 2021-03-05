#ifndef NWL_THREAD_H
#define NWL_THREAD_H
#include <nwl_core.hpp>
namespace NWL
{
	using thread = std::thread;
	using thread_locker = std::mutex;
}
#endif	// NWL_THREAD_H