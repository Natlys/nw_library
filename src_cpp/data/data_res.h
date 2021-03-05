#ifndef NWL_DATA_RES_H
#define NWL_DATA_RES_H
#include <nwl_core.hpp>
#include <core/nwl_info.h>
#include <core/nwl_string.h>
#include <memory/mem_sys.h>
namespace NWL
{
	/// abstract data_resource class
	/// interface:
	/// ->derrive any class you want from the a_data_res class
	/// ->implement save() and load() methods
	/// description:
	/// --every object in the engine can be saved in a binary file or some format
	/// --class which is inherit of a_data_res can be: saved | loaded
	/// --everything we need - save/load methods implementation for this
	class NWL_API a_data_res : public a_mem_user
	{
	protected:
		a_data_res() : m_name("none") { }
		a_data_res(cstring name) : m_name("none") { set_name(name); }
	public:
		virtual ~a_data_res() { }
		// --getters
		inline cstring get_name() const { return &m_name[0]; }
		// --setters
		virtual void set_name(const char* name) { m_name = name; }
		// --core_methods
		virtual bit save_file(cstring file_path) = 0;
		virtual bit load_file(cstring file_path) = 0;
	protected:
		dstring m_name;
	};
}

#endif // NWL_DATA_RES_H