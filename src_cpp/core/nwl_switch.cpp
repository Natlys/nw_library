#include <nwl_pch.hpp>
#include "nwl_switch.h"
#include <math/math_vector.h>
#include <math/math_matrix.h>
#include <io/io_exception.h>

namespace NWL
{
	PixelFormats PxfGet(UInt8 nChannels) {
		switch (nChannels) {
		case 1: return PXF_R8_UINT8;
		case 2: return PXF_R8G8_UINT16;
		case 3: return PXF_R8G8B8_UINT32;
		case 4: return PXF_R8G8B8A8_UINT32;
		default: break;
		}
		return PXF_DEFAULT;
	}
	UInt8 PxfGetChannels(PixelFormats pxlFormat) {
		switch (pxlFormat) {
		case PXF_R8_SINT8: case PXF_R8_UINT8:
		case PXF_D32_SINT32: case PXF_D32_UINT32:
		case PXF_S8_SINT8: case PXF_S8_UINT8:
		case PXF_R32_SINT32: case PXF_R32_UINT32:
			return 1;
		case PXF_R16G16_SINT32: case PXF_R16G16_UINT32:
		case PXF_D24S8_SINT32: case PXF_D24S8_UINT32:
			return 2;
		case PXF_R8G8B8_SINT32: case PXF_R8G8B8_UINT32:
			return 3;
		case PXF_R8G8B8A8_SINT32: case PXF_R8G8B8A8_UINT32:
			return 4;
		default: break;
		}
		return 0;
	}
}