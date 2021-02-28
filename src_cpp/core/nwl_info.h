#ifndef NWL_INFO_H
#define NWL_INFO_H
#include <nwl_core.hpp>
namespace NWL
{
	struct NWL_API AInfo
	{
	public:
		AInfo() = default;
		virtual ~AInfo() = default;
		// --operators
		virtual std::ostream& operator<<(std::ostream& rStream) const = 0;
		virtual std::istream& operator>>(std::istream& rStream) = 0;
	};
	std::ostream& operator<<(std::ostream& rStream, const AInfo& rInfo);
	std::istream& operator>>(std::istream& rStream, AInfo& rInfo);
}
#endif	// NWL_INFO_H