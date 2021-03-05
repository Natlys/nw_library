#include <nwl_pch.hpp>
#include "nwl_info.h"
namespace NWL
{
	// --operators
	std::ostream& a_info::operator<<(std::ostream& stm) const {
		return stm;
	}
	std::istream& a_info::operator>>(std::istream& stm) {
		return stm;
	}

	std::ostream& operator<<(std::ostream& stm, const a_info& info) { return info.operator<<(stm); }
	std::istream& operator>>(std::istream& stm, a_info& info) { return info.operator>>(stm); }
}