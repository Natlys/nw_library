#include <nwl_pch.hpp>
#include "io_log.h"

#include <memory/mem_sys.h>

#include <iomanip>

NW::log_sys::input* NW::log_sys::s_input = nullptr;
NW::log_sys::output* NW::log_sys::s_output = nullptr;

namespace NW
{
	// --==<core_methods>==--
	void log_sys::on_init()
	{
		if (s_input != nullptr) { return; }
		s_input = new input();
		s_output = &std::cout;

		// format flags;
		// use "flags" method to get them;
		// or "setf"/"unsetf" for individual setting;
		std::ios_base::fmtflags input_flags =
			std::ios_base::internal |		// central padding
			std::ios_base::boolalpha |		// true/false
			std::ios_base::oct |			// octodecimal
			std::ios_base::hex |			// hexadecimal
			std::ios_base::showbase |		// 0 or x before oct/hex
			std::ios_base::showpoint |		// no matter zeros;
			std::ios_base::uppercase;		//
		std::ios_base::fmtflags flag_fields =
			std::ios_base::basefield |		//
			std::ios_base::adjustfield |	// 
			std::ios_base::floatfield;		//
		std::cout.exceptions(std::ios_base::failbit | std::ios_base::badbit);
	}
	void log_sys::on_quit()
	{
		if (s_input == nullptr) { return; }
		delete s_input;
		s_input = nullptr;
		s_output = nullptr;
	}
	void log_sys::update()
	{
	}
	void log_sys::write_info(cstring format, ...)
	{
		va_list valArgs;
		va_start(valArgs, format);
		get_input() <<
			"--==<log_info>==--" << std::endl <<
			"::message:" << &str_format_var(format, valArgs)[0] << std::endl <<
			"--==</log_info>==--" << std::endl;
		va_end(valArgs);
	}
	void log_sys::write_warn(cstring format, ...)
	{
		va_list valArgs;
		va_start(valArgs, format);
		get_input() <<
			"--==<log_warning>==--" << std::endl <<
			"::message:" << &str_format_var(format, valArgs)[0] << std::endl <<
			"--==</log_warning>==--" << std::endl;
		va_end(valArgs);
		NW_BREAK();
	}
	void log_sys::write_error(error_codes err_code, cstring format, ...)
	{
		va_list valArgs;
		va_start(valArgs, format);
		get_input() <<
			"--==<log_error>==--" << std::endl <<
			"code:" << err_code << std::endl <<
			"::message:" << &str_format_var(format, valArgs)[0] << std::endl <<
			"--==</log_error>==--" << std::endl;
		va_end(valArgs);
		NW_BREAK();
	}
	// --==</core_methods>==--
}