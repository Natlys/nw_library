#ifndef NWL_CONTAINER_H
#define NWL_CONTAINER_H
#include <nwl_core.hpp>
namespace NWL
{
	template <typename vtype, size slots>
	using carray = std::array<vtype, slots>;
	template <typename vtype>
	using darray = std::vector<vtype>;
	template <typename vtype>
	using dstack = std::stack<vtype>;
	template <typename vtype>
	using list2links = std::list<vtype>;
	template <typename ktype, typename vtype>
	using dictionary = std::unordered_map<ktype, vtype>;
	template <typename type1, typename type2>
	using pair = std::pair<type1, type2>;
}
#endif	// NWL_CONTAINER_H