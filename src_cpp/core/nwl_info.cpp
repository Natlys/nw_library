#include <nwl_pch.hpp>
#include "nwl_info.h"
namespace NWL
{
	// --operators
	std::ostream& operator<<(std::ostream& rStream, const AInfo& rInfo) { return rInfo.operator<<(rStream); }
	std::istream& operator>>(std::istream& rStream, AInfo& rInfo) { return rInfo.operator>>(rStream); }
}