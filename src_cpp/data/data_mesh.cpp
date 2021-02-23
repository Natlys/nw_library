#include <nwl_pch.hpp>
#include "data_mesh.h"

#include <io/io_exception.h>

namespace NWL
{
	// --operators
	std::ostream& GfxMeshInfo::operator<<(std::ostream& rStream) const {
		return rStream <<
			"--==<graphics_mesh_info>==--" << std::endl <<
			"--==</graphics_mesh_info>==--" << std::endl;
	}
	std::istream& GfxMeshInfo::operator>>(std::istream& rStream) {
		return rStream;
	}

	std::ostream& operator<<(std::ostream& rStream, const GfxMeshInfo& rInfo) { return rInfo.operator<<(rStream); }
	std::istream& operator>>(std::istream& rStream, GfxMeshInfo& rInfo) { return rInfo.operator>>(rStream); }
}
namespace NWL
{
	// --operators
	std::ostream& GfxModelInfo::operator<<(std::ostream& rStream) const {
		return rStream <<
			"--==<graphics_model_info>==--" << std::endl <<
			"--==</graphics_model_info>==--" << std::endl;
	}
	std::istream& GfxModelInfo::operator>>(std::istream& rStream) {
		return rStream;
	}

	std::ostream& operator<<(std::ostream& rStream, const GfxModelInfo& rInfo) { return rInfo.operator<<(rStream); }
	std::istream& operator>>(std::istream& rStream, GfxModelInfo& rInfo) { return rInfo.operator>>(rStream); }
}