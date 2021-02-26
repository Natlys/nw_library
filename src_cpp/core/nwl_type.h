#ifndef NWL_TYPE_H
#define NWL_TYPE_H
#include <nwl_core.hpp>

namespace NWL
{
	class NWL_API TypeIndexator
	{
	public:
		template <class Type>
		static const UInt32 GetId() { static const UInt32 s_unTypeIdx{ s_unCount++ }; return s_unTypeIdx; }
		static const UInt32 GetId() { return s_unCount; }
	private:
		static UInt32 s_unCount;
	};
}

#endif	// NWL_TYPE_H