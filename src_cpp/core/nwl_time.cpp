#include <nwl_pch.hpp>
#include "nwl_time.h"
namespace NWL
{
	time_state::time_state() :
		m_tp_last(clock::now()), m_tp_curr(clock::now()),
		m_ncurr(0.0), m_nlast(0.0), m_ndelta(0.0),
		m_nbegin(0.0)
	{
		m_nbegin = sec(m_tp_curr - m_tp_last).count();
	}
	// --core_methods
	void time_state::update() {
		m_tp_curr = clock::now();
		m_ndelta = sec(m_tp_curr - m_tp_last).count();
		m_nlast = m_ncurr;
		m_ncurr += m_ndelta;
		m_tp_last = m_tp_curr;
	}
}