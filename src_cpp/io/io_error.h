#ifndef NW_IO_ERROR_H
#define NW_IO_ERROR_H
#include <nwl_core.hpp>
#include <core/nwl_string.h>
#include <core/nwl_switch.h>
namespace NW
{
	class NW_API error
	{
	public:
		error(cstring comment = "default", ui32 err_code = ERC_DEFAULT, cstring location = "default", ui32 line = -1);
		// --getters
		inline cstring get_string() const;
		inline error_codes get_code() const	{ return m_code; }
		inline cstring get_comment() const	{ return &m_comment[0]; }
		inline cstring get_location() const	{ return &m_location[0]; }
		inline ui32 get_line() const		{ return m_line; }
		// --operators
		std::ostream& operator<<(std::ostream& stm) const;
		std::istream& operator>>(std::istream& stm);
	private:
		dstring m_comment;
		error_codes m_code;
		dstring m_location;
		ui32 m_line;
	};
	std::ostream& operator<<(std::ostream& stm, const error& err);
	std::istream& operator>>(std::istream& stm, error& err);
}
#endif	// NW_IO_ERROR_H