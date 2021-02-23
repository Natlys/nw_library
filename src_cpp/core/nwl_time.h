#ifndef NWL_TIME_H
#define NWL_TIME_H

#include <nwl_core.hpp>

namespace NWL
{
	/// TimeCounter class
	class NWL_API TimeCounter
	{
		using Clock = std::chrono::high_resolution_clock;
		using TimePoint = std::chrono::time_point<Clock>;
		using Sec = std::chrono::duration<Float64, std::ratio<1>>;
	public:
		TimeCounter();
		// --getters
		inline Float64 GetCurr()	{ return m_nLast; }
		inline Float64 GetLast()	{ return m_nLast; }
		inline Float64 GetDelta()	{ return m_nCurr - m_nLast; }
		inline Float64 GetBegin()	{ return m_nBegin; }
		// --setters
		void Update();
		// --core_methods
	private:
		TimePoint m_tpLast;
		TimePoint m_tpCurr;
		Float64 m_nCurr;
		Float64 m_nLast;
		Float64 m_nDelta;
		Float64 m_nBegin;
	};
}
namespace NWL
{
	/// Time static class
	/// Description:
	/// -- The class for getting time. Update Method updates values
	class NWL_API TimeSys
	{
	public:
		// --getters
		static inline const TimeCounter& GetCounter()			{ return s_tCounter; }
		static inline Float64 GetCurr(Float64 nRatio = 1.0)		{ return s_tCounter.GetCurr() * nRatio; }
		static inline Float64 GetLast(Float64 nRatio = 1.0)		{ return s_tCounter.GetLast() * nRatio; }
		static inline Float64 GetDelta(Float64 nRatio = 1.0)	{ return s_tCounter.GetDelta() * nRatio; }
		static inline Float64 GetGlobal(Float64 nRatio = 1.0)	{ return s_tCounter.GetBegin() * nRatio; }
		static inline Float64 GetFPS(Float64 nRatio = 1.0)		{ return 1.0 / GetDelta(nRatio); }
		// --core_methods
		static void OnInit();
		static void OnQuit();
		static void Update();
	private:
		static TimeCounter s_tCounter;
	};
}

#endif // NW_TIME_H