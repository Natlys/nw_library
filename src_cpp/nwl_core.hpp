#ifndef NWL_CORE_HPP
#define NWL_CORE_HPP

// --==<configuration>==--
#if defined NWL_BUILD_LIB
	#define NWL_API
#else
#	if defined NWL_BUILD_DLL
#		define NWL_API __declspec(dllexport)
#	else
#		define NWL_API __declspec(dllimport)
#	endif
#endif
#define NWL_LAST_CLASS __declspec(novtable)

#ifdef _WIN32
#	define NWL_NEWLINE  "\r\n"
#else
#	define NWL_NEWLINE  "\n"
#endif
#if defined(_MSC_VER)
#	if (!(defined _CRT_SECURE_NO_WARNINGS) && false)
#		pragma warning (disable: 4996) // 'This function or variable may be unsafe': strcpy, strdup, sprintf, vsnprintf, sscanf, fopen
#		define _CRT_SECURE_NO_WARNINGS
#	endif
#endif	// microsoft visual studio version
// --==</configuration>==--

// --==<pragmas>==--
#pragma warning(disable : 4005)
#pragma warning(disable : 4081)
#pragma warning(disable : 4099)
#pragma warning(disable : 4102)
#pragma warning(disable : 4244)
#pragma warning(disable : 4251)
#pragma warning(disable : 4267)
#pragma warning(disable : 4273)
#pragma warning(disable : 4275)
#pragma warning(disable : 4551)
#pragma warning(disable : 4552)
#pragma warning(disable : 4996)
#ifdef _MSC_VER
#endif
// --==</pragmas>==--

#include <nwl_pch.hpp>

// --==<alias>==--
namespace NWL
{
	using Int8 = __int8;
	using Int16 = __int16;
	using Int32 = __int32;
	using Int64 = long int;
	using UInt8 = unsigned __int8;
	using UInt16 = unsigned __int16;
	using UInt32 = unsigned __int32;
	using UInt64 = unsigned long int;
	using Float32 = float;
	using Float64 = double;
	using Float128 = long double;
	using Ptr = void*;
	using Bit = bool;
	using Byte = char;
	using UByte = unsigned char;
	using Size = size_t;
	using Char = char;
	using UChar = unsigned char;
	using Char8 = char;
	using UChar8 = unsigned char;
	using WChar = wchar_t;
	using Char16 = wchar_t;
}
// --==</alias>==--

// --==<support_macroses>==--
#define NWL_XY_TO_X(x, y, w) ( (static_cast<Size>(y) * static_cast<Size>(w)) + static_cast<Size>(x) )
#define NWL_ALIGN_FORWARD(sz_data, sz_alignment) ( (static_cast<Size>(sz_data) + (static_cast<Size>(sz_alignment) - 1)) & ~(static_cast<Size>(sz_alignment) - 1) )

#if (defined NWL_DEBUG)
#	define NWL_BREAK() (__debugbreak())
#	define NWL_ASSERT(expr, comment) if (expr == false) { std::cout << comment; NWL_BREAK(); }
#	define NWL_ERR(comment) NWL_ASSERT(false, comment);
// --==</support_macroses>==--
#else
#	define NWL_BREAK()
#	define NWL_ASSERT(expt, comment)
#	define NWL_ERR(comment)
#endif	// NWL_DEBUG

namespace NWL
{
	template<class SType>
	class NWL_API ASingleton;
	template<class EType, class SType>
	class NWL_API AEngine;
	class NWL_API AEngineState;
	class NWL_API ADataRes;
	struct NWL_API AEvent;
	struct NWL_API WindowEvent;
	struct NWL_API CursorEvent;
	struct NWL_API KeyboardEvent;
}
namespace NWL
{
	enum Constants : UInt32 {
		C_DEFAULT = 0,
		C_ZERO = 0, C_NULL = 0, C_FALSE = 0,
		C_ONE = 1, C_TRUE = 1
	};
	enum DataTypes : UInt32 {
		DT_DEFAULT = C_DEFAULT,
		DT_BOOL = 1,
		DT_VEC2_BOOL, DT_VEC3_BOOL, DT_VEC4_BOOL,
		DT_MAT2_BOOL, DT_MAT3_BOOL, DT_MAT4_BOOL,
		DT_SINT8,
		DT_VEC2_SINT8, DT_VEC3_SINT8, DT_VEC4_SINT8,
		DT_MAT2_SINT8, DT_MAT3_SINT8, DT_MAT4_SINT8,
		DT_UINT8,
		DT_VEC2_UINT8, DT_VEC3_UINT8, DT_VEC4_UINT8,
		DT_MAT2_UINT8, DT_MAT3_UINT8, DT_MAT4_UINT8,
		DT_SINT16,
		DT_VEC2_SINT16, DT_VEC3_SINT16, DT_VEC4_SINT16,
		DT_MAT2_SINT16, DT_MAT3_SINT16, DT_MAT4_SINT16,
		DT_UINT16,
		DT_VEC2_UINT16, DT_VEC3_UINT16, DT_VEC4_UINT16,
		DT_MAT2_UINT16, DT_MAT3_UINT16, DT_MAT4_UINT16,
		DT_SINT32,
		DT_VEC2_SINT32, DT_VEC3_SINT32, DT_VEC4_SINT32,
		DT_MAT2_SINT32, DT_MAT3_SINT32, DT_MAT4_SINT32,
		DT_UINT32,
		DT_VEC2_UINT32, DT_VEC3_UINT32, DT_VEC4_UINT32,
		DT_MAT2_UINT32, DT_MAT3_UINT32, DT_MAT4_UINT32,
		DT_FLOAT32,
		DT_VEC2_FLOAT32, DT_VEC3_FLOAT32, DT_VEC4_FLOAT32,
		DT_MAT2_FLOAT32, DT_MAT3_FLOAT32, DT_MAT4_FLOAT32,
		DT_FLOAT64,
		DT_VEC2_FLOAT64, DT_VEC3_FLOAT64, DT_VEC4_FLOAT64,
		DT_MAT2_FLOAT64, DT_MAT3_FLOAT64, DT_MAT4_FLOAT64,
		DT_USER_DATA = 99
	};
	enum TextureTypes : UInt32 {
		TXT_DEFAULT = C_DEFAULT,
		TXT_1D = 1, TXT_2D = 2, TXT_3D = 3,
		TXT_2D_MULTISAMPLE, TXT_3D_MULTISAMPLE
	};
	enum TextureWraps : UInt32 {
		TXW_DEFAULT = C_DEFAULT,
		TXW_REPEAT = 1, TXW_CLAMP = 2, TXW_BORDER = 3,
	};
	enum TextureFilters : UInt32 {
		TXF_DEFAULT = C_DEFAULT,
		TXF_LINEAR, TXF_NEAREST,
	};
	enum PixelFormats : UInt32 {
		PXF_DEFAULT = C_DEFAULT,
		PXF_R8_SINT8,
		PXF_R8_UINT8,
		PXF_R16_SINT16, PXF_R8G8_SINT16,
		PXF_R16_UINT16, PXF_R8G8_UINT16,
		PXF_R32_SINT32, PXF_R16G16_SINT32, PXF_R8G8B8_SINT32, PXF_R8G8B8A8_SINT32,
		PXF_R32_UINT32, PXF_R16G16_UINT32, PXF_R8G8B8_UINT32, PXF_R8G8B8A8_UINT32,
		PXF_S8_SINT8, PXF_D32_SINT32,
		PXF_S8_UINT8, PXF_D32_UINT32,
		PXF_D24S8_SINT32,
		PXF_D24S8_UINT32,
	};
	enum FacePlanes : UInt32 {
		FACE_DEFAULT = C_DEFAULT,
		FACE_FRONT_AND_BACK = 1,
		FACE_BACK, FACE_FRONT, FACE_LEFT, FACE_RIGTH,
	};
	enum Directions : UInt32 {
		DIR_DEFAULT = C_DEFAULT,
		DIR_NORTH = 1, DIR_SOUTH = 2,
		DIR_EAST = 3, DIR_WEST = 4,
	};
	enum ErrorCodes : UInt32 {
		ERC_DEFAULT = C_DEFAULT,
		ERC_NO_INIT = 1, ERC_NO_QUIT = 2,
		ERC_NO_SUPPORT, ERC_NO_STATE,
		ERC_NO_LOAD, ERC_NO_SAVE,
		ERC_DATA_BAD, ERC_DATA_LOSS, ERC_DATA_OVERFLOW, ERC_DATA_UNDERFLOW,
		ERC_UNKNOWN_ID, ERC_UNKNOWN_NAME,
		ERC_INVALID_FORMAT, ERC_INVALID_SYNTAX, ERC_INVALID_TYPE, ERC_INVALID_ENUM,
		ERC_COMPILLATION, ERC_LINKAGE
	};
	enum LogicalOpers : UInt32 {
		LO_DEFAULT = C_DEFAULT,
		LO_EQUAL = 1, LO_GREATER = 2, LO_LESSER = 2,
		LO_GEQUAL, LO_LEQUAL,
	};
}
#endif	// NWL_CORE_HPP