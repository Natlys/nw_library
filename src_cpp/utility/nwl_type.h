#ifndef NWL_TYPE_H
#define NWL_TYPE_H

#include <nwl_core.hpp>

namespace NWL
{
	using TypeId = UInt32;
	using TypeInfo = std::type_index;
}
namespace NWL
{
	class NWL_API TypeIndexator
	{
	public:
		template <class Type>
		static const TypeId Get() { static const TypeId s_unTypeIdx{ s_unCount++ }; return s_unTypeIdx; }
		static const TypeId Get() { return s_unCount; }
	private:
		static TypeId s_unCount;
	};
}

#endif	// NWL_TYPE_H