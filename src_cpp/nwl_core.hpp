#ifndef NWL_CORE_HPP
#define NWL_CORE_HPP

// --==<configuration>==--
#if (defined NWL_PLATFORM_WINDOWS)
	#if defined NWL_LINK_DYNAMIC
		#ifdef NWL_BUILD_DLL
			#define NWL_API __declspec(dllexport)
		#elif defined NWL_BUILD_EXE
			#define NWL_API __declspec(dllimport)
		#endif
	#elif defined NWL_LINK_STATIC
		#define NWL_API
	#endif
#endif	// NWL_PLATFORM
// --==</linking>==--

// --==</configuration>==--

#include <nwl_pch.hpp>

// --==<alias>==--
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
#if defined NWL_PLATFORM_WINDOWS
using V2xy = COORD;
using V2wh = COORD;
using V4xywh = SMALL_RECT;
using CPixel = CHAR_INFO;
using CSBufInfo = CONSOLE_SCREEN_BUFFER_INFO;
using CSBufInfoX = CONSOLE_SCREEN_BUFFER_INFOEX;
using CCursorInfoT = CONSOLE_CURSOR_INFO;
using CFontInfoX = CONSOLE_FONT_INFOEX;
#endif // NWL_PLATFORM
// --==</alias>==--

// --==<support_macroses>==--
#define NWL_CSTR(anything) (#anything)
#define NWL_STR(anything) (std::string(anything))
#define NWL_STR_FORM(format, args);
#define NWL_STR_PART_L(str, symb) ( ( str.substr(0, str.rfind(symb) + 1) ).c_str() )
#define NWL_STR_PART_R(str, symb) ( ( str.substr(str.rfind(symb) + 1, str.size()) ).c_str() )
#define NWL_FNAME_APATH(path) ( NWL_STR_PART_R(std::string(path), '\\') )
#define NWL_FDIR_APATH(path) ( NWL_STR_PART_L(std::string(path), '\\') )

#define NWL_BIND_FN(func) (std::bind(&func, this, std::placeholders::_1))

#define NWL_XY_TO_X(x, y, w) ((static_cast<Size>(y) * static_cast<Size>(w)) + static_cast<Size>(x))

#define NWL_FIND_BY_FUNC(Container, Type, val, func) std::find_if(Container.begin(), Container.end(),	\
	[=](Type Obj)->bool {return Obj func() == val; });
#define NWL_FIND_BY_NAME(Container, Type, val, func) std::find_if(Container.begin(), Container.end(),	\
	[=](Type Obj)->bool {return (strcmp(&(Obj func())[0], val) == 0); });

// --debug_macro
#if (defined NWL_DEBUG)
/// Print the calling location and the message
/// --Writes LOG::[location]::LINE_{calling_line}:
///	====< msg >====\n
#define NWL_LOG_LOC(loc) std::cout << "LOG::[" << loc <<				\
			"]::LINE_" << __LINE__ << std::endl
#define NWL_LOG(msg) NWL_LOG_LOC(NWL_FNAME_APATH(__FILE__));			\
		std::cout << "====< " << msg << " >====\n";
	/// --Takes format string where [param] means next string
	/// --Example: NWL_LOG_F("Format message [param] sometext", nextString)
	/// --Writes: LOG::[FILE_NAME]::LILE_[CURR_LINE]:
	///	====< Format message nextString sometext >====
#define NWL_LOG_F(format, ...) {										\
		const char* msg = format; int i = 0;							\
		char ch = 'a';	std::stringstream sStr;							\
		while(ch != '\0') { ch = msg[i];								\
			if (ch == '{') while(true) { ch = msg[i + 1];				\
				if (ch == '\0') break;									\
				else if (ch == '}'){sStr << __VA_ARGS__; break;}		\
				i++; }													\
			else {sStr << msg[i];}										\
		i++; }															\
		NW_LOG(sStr.str());												\
	}
#define NWL_BREAK() __debugbreak();
#define NWL_ASSERT(expr, comment) if (!(expr)) { std::cout <<			\
		"NWL::ASSERT::[" << __FILE__ <<									\
		"]::LINE_" << __LINE__ << ":\n" << comment << ">>\n";			\
	NWL_BREAK(); }
#define NWL_ERR(comment) NWL_ASSERT(false, comment);
// --==</support_macroses>==--
#else
#define NWL_LOG_LOC(loc)
#define NWL_LOG(msg)
#define NWL_LOG_F(format, ...)
#define NWL_BREAK()
#define NWL_ASSERT(expt, comment)
#define NWL_ERR(comment)
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

// --==<nwl_error_codes>==--
#define NWL_ERR_DATA_LOSS				0b1110'0000'0000

#define NWL_ERR_NO_SUPPORT				0b1110'0000'0001
#define NWL_ERR_NO_DATA					0b1110'0000'0001
#define NWL_ERR_NO_INIT					0b1110'0000'0010
#define NWL_ERR_NO_QUIT					0b1110'0000'0011
#define NWL_ERR_NO_STATE				0b1110'0000'0100

#define NWL_ERR_UNKNOWN_ID				0b1111'0000'0000

#define NWL_ERR_SHADER_INVALID_FORMAT	0b0011'0000'0000
#define NWL_ERR_SHADER_LOAD_PATH		0b1000'0000'0000
#define NWL_ERR_SHADER_LOAD_FAIL		0b1001'0000'0000
#define NWL_ERR_SHADER_LINK				0b1011'0000'0000
#define NWL_ERR_SHADER_COMPILE			0b1100'0000'0000
// --==</nwl_error_codes>==--

#endif	// NWL_CORE_HPP