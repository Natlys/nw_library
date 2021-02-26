#ifndef NWL_DATA_MESH_H
#define NWL_DATA_MESH_H
#include <nwl_core.hpp>
#include <core/nwl_string.h>
#include <core/nwl_switch.h>
#include <core/nwl_container.h>
#include <math/math_vector.h>
#include <math/math_matrix.h>
namespace NWL
{
	struct NWL_API Vtx2f
	{
		V2f vtxCrd = { 0.0f, 0.0f };
	};
	struct NWL_API Vtx2f2f
	{
		V2f vtxCrd = { 0.0f, 0.0f };
		V2f texCrd = { 0.0f, 0.0f };
	};
	struct NWL_API Vtx2f2f4u8
	{
		V2f vtxCrd = { 0.0f, 0.0f };
		V2f texCrd = { 0.0f, 0.0f };
		V4u8 vtxClr = { 0u, 0u, 0u, 0u };
	};
	struct NWL_API Vtx3f
	{
		V3f vtxCrd = { 0.0f, 0.0f, 0.0f };
	};
	struct NWL_API Vtx3f2f3f
	{
		V3f vtxCrd = { 0.0f, 0.0f, 0.0f };
		V2f texCrd = { 0.0f, 0.0f };
		V3f nrmCrd = { 0.0f, 0.0f, 0.0f };
	};
}
namespace NWL
{
	struct NWL_API SBuf1Mat4f {
		Mat4f m4Model = Mat4f(1.0f);
	};
	struct NWL_API SBuf2Mat4f {
		Mat4f m4View = Mat4f(1.0f);
		Mat4f m4Proj = Mat4f(1.0f);
	};
	struct NWL_API SBuf3Mat4f {
		Mat4f m4Model = Mat4f(1.0f);
		Mat4f m4View = Mat4f(1.0f);
		Mat4f m4Proj = Mat4f(1.0f);
	};
}
namespace NWL
{
	struct NWL_API VertexDataInfo
	{
	public:
	};
	/// TriangleList class
	template<typename VType, typename IType = UInt32>
	class NWL_API TriangleList
	{
	public:
		DArray<VType> vtxData;
		DArray<IType> idxData;
	public:
		TriangleList(DArray<VType>& rVtxData, DArray<IType>& rIdxData) :
			vtxData(rVtxData), idxData(rIdxData) {
			Remake();
		}
		~TriangleList() = default;
		// --getters
		inline DataTypes GetVtxType() const { return ConvertEnum<VType, DataTypes>(); }
		inline DataTypes GetIdxType() const { return ConvertEnum<IType, DataTypes>(); }
		// --setters
		// --core_methods
		inline void Remake(DArray<VType>& rVtxData, DArray<IType>& rIdxData) { vtxData = rVtxData; rIdxData = rIdxData; }
		inline void Remake() {}
	};
}
#endif	// NWL_DATA_MESH_H