#ifndef NWL_TIME_H
#define NWL_TIME_H

#include <nwl_core.hpp>

#include <ctime>
#include <time.h>

namespace NWL
{
	using TimeInfo = tm;
	/// RealTimeCounter class
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

#endif // NW_TIME_H