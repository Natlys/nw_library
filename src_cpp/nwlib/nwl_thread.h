#ifndef NWL_THREAD_H
#define NWL_THREAD_H

#include <nwl_core.hpp>

#include <thread>
#include <atomic>
#include <condition_variable>
#include <future>
#include <mutex>

namespace NWL
{
	using Thread = std::thread;
	using Mutex = std::mutex;
}

#endif	// NWL_THREAD_H