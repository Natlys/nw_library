#include <nwl_pch.hpp>
#include "data_rsc.h"
namespace NW
{
	a_data_rsc::a_data_rsc(cstring name) :
		m_name(name) { }
	a_data_rsc::~a_data_rsc() { }
	// -- setters
	void a_data_rsc::set_name(cstring name) { m_name = name; }
	// operators
	out_stream& a_data_rsc::operator<<(out_stream& stm) const {
		return stm << m_name << ";";
	}
	in_stream& a_data_rsc::operator>>(in_stream& stm) {
		return stm;
	}

	out_stream& operator<<(out_stream& stm, const a_data_rsc& rsc) { return rsc.operator<<(stm); }
	in_stream& operator>>(in_stream& stm, a_data_rsc& rsc) { return rsc.operator>>(stm); }
}