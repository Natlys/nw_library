#ifndef NWL_INFO_H
#define NWL_INFO_H
#include <nwl_core.hpp>
namespace NWL
{
	struct NWL_API a_info
	{
	public:
		a_info() = default;
		virtual ~a_info() = default;
		// --operators
		virtual std::ostream& operator<<(std::ostream& stm) const;
		virtual std::istream& operator>>(std::istream& stm);
	};
	std::ostream& operator<<(std::ostream& stm, const a_info& info);
	std::istream& operator>>(std::istream& stm, a_info& info);
}
#endif	// NWL_INFO_H