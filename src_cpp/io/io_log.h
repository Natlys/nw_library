#ifndef NWL_IO_LOG_H
#define NWL_IO_LOG_H
#include <nwl_core.hpp>
#include <io/io_stream.h>
#include <core/nwl_string.h>
#include <core/nwl_switch.h>
namespace NWL
{
	/// log_system static class
	class NWL_API log_sys
	{
	public:
		using input = str_stream;
		using output = out_stream;
	public:
		// --getters
		static inline input& get_input() { return *s_input; }
		static inline output& get_output() { return *s_output; }
		// --setters
		static void on_init();
		static void on_quit();
		static void update();
		static void set_output(output& out);
		// --core_methods
		static void write_info(cstring format, ...);
		static void write_error(error_codes err_code, cstring format, ...);
		static void write_warn(cstring format, ...);
	private:
		static input* s_input;
		static output* s_output;
	};
}
#endif // NWL_IO_LOG_H