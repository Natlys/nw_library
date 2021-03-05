#ifndef NWL_TIME_H
#define NWL_TIME_H
#include <nwl_core.hpp>
namespace NWL
{
	/// timer class
	class NWL_API timer
	{
		using clock = std::chrono::high_resolution_clock;
		using time_point = std::chrono::time_point<clock>;
		using sec = std::chrono::duration<f64, std::ratio<1>>;
		using millisec = std::chrono::duration<f64, std::milli>;
	public:
		timer();
		// --getters
		inline f64 get_curr(f64 nratio = 1.0) const		{ return m_ncurr * nratio; }
		inline f64 get_last(f64 nratio = 1.0) const		{ return m_nlast * nratio; }
		inline f64 get_delta(f64 nratio = 1.0) const	{ return m_ndelta * nratio; }
		inline f64 get_begin(f64 nratio = 1.0) const	{ return m_nbegin * nratio; }
		inline f64 get_ups(f64 nratio = 1.0) const		{ return 1.0 / m_ndelta * nratio; }
		// --setters
		void update();
		// --core_methods
	private:
		time_point m_tp_curr;
		time_point m_tp_last;
		f64 m_ncurr;
		f64 m_nlast;
		f64 m_ndelta;
		f64 m_nbegin;
	};
}
#endif // NW_TIME_H