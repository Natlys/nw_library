#ifndef NWL_DATA_SYSTEM_H
#define NWL_DATA_SYSTEM_H
#include <nwl_core.hpp>
#include <core/nwl_info.h>
#include <data/data_res.h>
namespace NWL
{
	/// data_sys static class
	class NWL_API data_sys
	{
	public:
		// --getters
		static inline cstring GetDirectory() { return &s_strDir[0]; }
		// --core_methods
		static void on_init();
		static void on_quit();
		// --loading
		static dstring dialog_load(cstring filter, ptr user_data);
		static bit load_file(cstring file_path, ptr data, size nof_bytes);
		static bit load_file(cstring file_path, dstring& data);
		static bit load_file(cstring file_path, a_info& data);
		// --saving
		static dstring dialog_save(cstring filter, ptr user_data);
		static bit save_file(cstring file_path, ptr data, size nof_bytes);
		static bit save_file(cstring file_path, dstring& data);
		static bit save_file(cstring file_path, a_info& data);
	private:
		static dstring s_strDir;
	};
}

#endif	// NWL_DATA_SYSTEM_H