#ifndef NWL_TYPE_H
#define NWL_TYPE_H
#include <nwl_core.hpp>
namespace NWL
{
	class NWL_API type_indexator
	{
	public:
		template <typename type>
		static const ui32 get_id() { static const ui32 s_type_id{ s_ncount++ }; return s_type_id; }
		static const ui32 get_id() { return s_ncount; }
	private:
		static ui32 s_ncount;
	};
}
#endif	// NWL_TYPE_H