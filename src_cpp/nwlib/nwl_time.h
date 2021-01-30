#ifndef NWL_TIME_H
#define NWL_TIME_H

#include <nwl_core.hpp>
#include <nwlib/nwl_string.h>

#include <ctime>
#include <time.h>

#pragma warning (disable : 4996)

namespace NWL
{
	struct NWL_API TimeInfo
	{
	public:
		String strTime = "";
		Float64 nCurr = 0;
		Float64 nLast = 0;
		Float64 nDelta = 0;
	};
}
namespace NWL
{
	/// TimeCounter class
	class NWL_API TimeCounter
	{
	public:
		TimeCounter() : m_nBegTime(0), m_nEndTime(0), m_nCreationTime(0) {}

		// --getters
		inline float GetCreationTime() { return m_nCreationTime; }
		inline float GetCountedTime() { return m_nEndTime - m_nBegTime; }
		// --setters
		void BeginCount() {}
		void EndCount() {}

		// --core_methods
	private:
		float m_nBegTime;
		float m_nEndTime;
		float m_nCreationTime;
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
		static inline TimeInfo& GetInfo()		{ static TimeInfo s_tmInfo; return s_tmInfo; }
		static inline Float64 GetLastS()		{ return GetInfo().nLast / 1000; }
		static inline Float64 GetCurrS()		{ return GetInfo().nCurr / 1000; }
		static inline Float64 GetDeltaS()		{ return GetInfo().nDelta / 1000; }
		static inline Float64 GetLastMs()		{ return GetInfo().nLast; }
		static inline Float64 GetCurrMs()		{ return GetInfo().nCurr; }
		static inline Float64 GetDeltaMs()		{ return GetInfo().nDelta; }
		static inline const char* GetString()	{ GetInfo().strTime = std::ctime(0); return &(GetInfo().strTime[0]); }
		static inline TimeCounter& GetCounter()	{ static TimeCounter s_tc; return s_tc; }
		// --core_methods
		static inline void Update();
	};
	inline void TimeSys::Update() {
		TimeInfo& tm = GetInfo();
		tm.nCurr = clock();
		tm.nDelta = tm.nCurr - tm.nLast;
		tm.nLast = tm.nCurr;
	}
}

#endif // NW_TIME_H