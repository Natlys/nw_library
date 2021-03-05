#include <nwl_pch.hpp>
#include "io_log.h"

#include <memory/mem_sys.h>

NWL::log_sys::input* NWL::log_sys::s_input = nullptr;
NWL::log_sys::output* NWL::log_sys::s_output = nullptr;

namespace NWL
{
	// --==<core_methods>==--
	void log_sys::on_init()
	{
		if (s_input != nullptr) { return; }
		s_input = new input();
		s_output = &std::cout;
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
		if (get_input().eof()) { return; }
		get_output() << get_input().rdbuf();
		get_input().clear();
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
		NWL_BREAK();
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
		NWL_BREAK();
	}
	// --==</core_methods>==--
}