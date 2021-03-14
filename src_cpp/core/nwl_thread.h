#ifndef NW_THREAD_H
#define NW_THREAD_H
#include <nwl_core.hpp>
namespace NW
{
	using thread = std::thread;
	using thread_locker = std::mutex;
}
#endif	// NW_THREAD_H