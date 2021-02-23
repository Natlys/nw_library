#ifndef NWL_DATA_MESH_H
#define NWL_DATA_MESH_H

#include <nwl_core.hpp>

#include <core/nwl_container.h>
#include <core/nwl_string.h>

namespace NWL
{
	/// GraphicalMeshInfo struct
	struct NWL_API GfxMeshInfo
	{
	public:
		String strName;
		String strMtlName;
		DArray<Byte> vtxData;
		DArray<Byte> idxData;
		DArray<Byte> vtxDataBox;
	public:
		// --operators
		std::ostream& operator<<(std::ostream& rStream) const;
		std::istream& operator>>(std::istream& rStream);
	};
	std::ostream& operator<<(std::ostream& rStream, const GfxMeshInfo& rModelInfo);
	std::istream& operator>>(std::istream& rStream, GfxMeshInfo& rModelInfo);
	/// GraphicalModelInfo struct
	struct NWL_API GfxModelInfo
	{
	public:
		String strName;
		DArray<GfxMeshInfo> Meshes;
	public:
		// --operators
		std::ostream& operator<<(std::ostream& rStream) const;
		std::istream& operator>>(std::istream& rStream);
	};
	std::ostream& operator<<(std::ostream& rStream, const GfxModelInfo& rModelInfo);
	std::istream& operator>>(std::istream& rStream, GfxModelInfo& rModelInfo);
}
#endif	// NWL_DATA_MESH_H