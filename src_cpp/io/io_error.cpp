#include <nwl_pch.hpp>
#include "io_error.h"
namespace NWL
{
	error::error(cstring comment, ui32 err_code, cstring location, ui32 line) :
		m_comment(comment), m_location(location), m_code(static_cast<error_codes>(err_code)), m_line(line)
	{
		NWL_ERR(get_string());
	}
	// --getters
	inline cstring error::get_string() const {
		str_stream stm;
		this->operator<<(stm);
		return &(stm.str())[0];
	}
	// --operators
	std::ostream& error::operator<<(std::ostream& stm) const {
		return stm <<
			"--==<exception_info>==--" << std::endl <<
			"string: " << get_comment() << std::endl <<
			"code: " << get_code() << std::endl <<
			"location: " << get_location() << std::endl <<
			"line: " << get_line() << std::endl <<
			"--==</exception_info>==--" << std::endl;
	}
	std::istream& error::operator>>(std::istream& stm) {
		return stm;
	}
	std::ostream& operator<<(std::ostream& stm, const error& err) { return err.operator<<(stm); }
	std::istream& operator>>(std::istream& stm, error& err) { return err.operator>>(stm); }
}