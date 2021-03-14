#ifndef NW_DATA_SYSTEM_H
#define NW_DATA_SYSTEM_H
#include <nwl_core.hpp>
#include "data_rsc.h"
#if (defined NW_OS)
namespace NW
{
	/// data_system static class
	class NW_API data_sys
	{
	public:
		// --getters
		static cstring get_path();
		static cstring get_path(cstring file_path);
		// --setters
		static void set_dir_root(cstring root_directory);
		// --core_methods
		static void on_init();
		static void on_quit();
		// --loading
		static cstring dialog_load(cstring filter, const window_handle& wnd);
		static bit load_file(cstring file_path, ptr data, size nof_bytes);
		static bit load_file(cstring file_path, dstring& data);
		static bit load_file(cstring file_path, a_data_rsc& data);
		// --saving
		static cstring dialog_save(cstring filter, const window_handle& wnd);
		static bit save_file(cstring file_path, ptr data, size nof_bytes);
		static bit save_file(cstring file_path, dstring& data);
		static bit save_file(cstring file_path, a_data_rsc& data);
	private:
		static dstring s_root_path;
		static dstring s_temp_path;
	};
}
#endif	// NW_OS
#endif	// NW_DATA_SYSTEM_H