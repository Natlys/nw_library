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
#	define NWL_NLINE  "\r\n"
#else
#	define NWL_NLINE  "\n"
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
using si8 =		signed __int8;
using si16 =	signed __int16;
using si32 =	signed __int32;
using si64 =	signed __int64;
using ui8 =		unsigned __int8;
using ui16 =	unsigned __int16;
using ui32 =	unsigned __int32;
using ui64 =	unsigned long int;
using f32 =		float;
using f64 =		double;
using f128 =	long double;
using ptr =		void*;
using cptr =	const void*;
using bit =		bool;
using sbyte =	char;
using ubyte =	unsigned char;
using size =	size_t;
using schar =	char;
using uchar =	unsigned char;
using wchar =	wchar_t;
// --==</alias>==--

// --==<support_macroses>==--
#define NWL_XY_TO_X(x, y, w) ( (static_cast<size>(y) * static_cast<size>(w)) + static_cast<size>(x) )
#define NWL_ALIGN_FORWARD(data, alignment) ( (static_cast<size>(data) + (static_cast<size>(alignment) - 1)) & ~(static_cast<size>(alignment) - 1) )

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
	template<class stype>
	class NWL_API a_singleton;
	class NWL_API a_data_res;
	struct NWL_API a_event;
	struct NWL_API window_event;
	struct NWL_API cursor_event;
	struct NWL_API keyboard_event;
}
#endif	// NWL_CORE_HPP