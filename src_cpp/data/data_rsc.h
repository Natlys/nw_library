#ifndef NW_DATA_RESOURCE_H
#define NW_DATA_RESOURCE_H
#include <nwl_core.hpp>
#include <core/nwl_string.h>
#include <io/io_stream.h>
#include <memory/mem_sys.h>
namespace NW
{
	/// abstract data_rscource class
	/// interface:
	/// ->derrive any class you want from the a_data_rsc class
	/// ->implement save() and load() methods
	/// description:
	/// --every object in the engine can be saved in a binary file or some format
	/// --class which is inherit of a_data_rsc can be: saved | loaded
	/// --everything we need - save/load methods implementation for this
	class NW_API a_data_rsc : public a_mem_user
	{
	protected:
		a_data_rsc(cstring name);
	public:
		virtual ~a_data_rsc();
		// --getters
		inline cstring get_name() const { return &m_name[0]; }
		// --setters
		virtual void set_name(cstring name);
		// --core_methods
		bit save_file(cstring file_path);
		bit load_file(cstring file_path);
		// --operators
		virtual out_stream& operator<<(out_stream& stm) const;
		virtual in_stream& operator>>(in_stream& stm);
	protected:
		dstring m_name;
	};
	out_stream& operator<<(out_stream& stm, const a_data_rsc& rsc);
	in_stream& operator>>(in_stream& stm, a_data_rsc& rsc);
}

#endif // NW_DATA_RESOURCE_H