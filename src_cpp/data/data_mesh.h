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
	struct NWL_API vtx2f
	{
		v2f32 vtx_crd = { 0.0f, 0.0f };
	};
	struct NWL_API vtx2f2f
	{
		v2f32 vtx_crd = { 0.0f, 0.0f };
		v2f32 tex_crd = { 0.0f, 0.0f };
	};
	struct NWL_API vtx2f2f4u8
	{
		v2f32 vtx_crd = { 0.0f, 0.0f };
		v2f32 tex_crd = { 0.0f, 0.0f };
		v4ui8 vtx_clr = { 0u, 0u, 0u, 0u };
	};
	struct NWL_API vtx3f
	{
		v3f32 vtx_crd = { 0.0f, 0.0f, 0.0f };
	};
	struct NWL_API vtx3f2f3f
	{
		v3f32 vtx_crd = { 0.0f, 0.0f, 0.0f };
		v2f32 tex_crd = { 0.0f, 0.0f };
		v3f32 nrm_crd = { 0.0f, 0.0f, 0.0f };
	};
}
namespace NWL
{
	struct NWL_API buf1m4f {
		m4f32 m4model = m4f32(1.0f);
	};
	struct NWL_API buf2m4f {
		m4f32 m4view = m4f32(1.0f);
		m4f32 m4proj = m4f32(1.0f);
	};
	struct NWL_API buf3m4f {
		m4f32 m4model = m4f32(1.0f);
		m4f32 m4view = m4f32(1.0f);
		m4f32 m4proj = m4f32(1.0f);
	};
}
#endif	// NWL_DATA_MESH_H