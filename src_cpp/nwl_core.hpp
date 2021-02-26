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
#endif	// NWL_CORE_HPP