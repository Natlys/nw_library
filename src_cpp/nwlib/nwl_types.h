#ifndef NWL_TYPES_H
#define NWL_TYPES_H

#include <nwl_core.hpp>
#include <typeindex>
#include <typeinfo>

namespace NWL
{
	using TypeInfo = std::type_index;
}
namespace NWL
{
	class NWL_API TypeIndexator
	{
	public:
		template <class IType>
		static const UInt32 GetIdx() { static const UInt32 s_unTypeIdx{ s_unCount++ }; return s_unTypeIdx; }
		static const UInt32 GetIdx() { return s_unCount; }
	private:
		static UInt32 s_unCount;
	};
}

#endif	// NWL_TYPES_H