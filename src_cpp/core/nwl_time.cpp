#include <nwl_pch.hpp>
#include "nwl_time.h"

namespace NWL
{
	TimeCounter::TimeCounter() :
		m_tpLast(Clock::now()), m_tpCurr(Clock::now()),
		m_nCurr(0.0), m_nLast(0.0), m_nDelta(0.0),
		m_nBegin(0.0)
	{
		m_nBegin = Sec(m_tpCurr - m_tpLast).count();
	}
	// --core_methods
	void TimeCounter::Update() {
		m_tpCurr = Clock::now();
		m_nDelta = Sec(m_tpCurr - m_tpLast).count();
		m_nLast = m_nCurr;
		m_nCurr += m_nDelta;
		m_tpLast = m_tpCurr;
	}
}
NWL::TimeCounter NWL::TimeSys::s_tCounter = TimeCounter();
namespace NWL
{
	// --==<core_methods>==--
	void TimeSys::OnInit() { s_tCounter = TimeCounter(); }
	void TimeSys::OnQuit() { }
	void TimeSys::Update() {
		s_tCounter.Update();
	}
	// --==</core_methods>==--
}