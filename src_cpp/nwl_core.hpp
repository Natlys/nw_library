#ifndef NWL_CORE_HPP
#define NWL_CORE_HPP

// --==<linking>==--
#if defined NWL_LINK_DYNAMIC
#ifdef NWL_BUILD_DLL
#define NWL_API __declspec(dllexport)
#elif defined NWL_BUILD_EXE
#define NWL_API __declspec(dllimport)
#endif
#else
#define NWL_API
#endif
// --==</linking>==--

// --==<alias>==--
using Int8 = __int8;
using Int16 = __int16;
using Int32 = __int32;
using Int64 = __int64;
using UInt8 = unsigned __int8;
using UInt16 = unsigned __int16;
using UInt32 = unsigned __int32;
using UInt64 = unsigned __int64;
using Float32 = float;
using Float64 = double;
using float128 = long double;
using Ptr = void*;
using Bit = bool;
using Byte = char;
using UByte = unsigned char;
using Size = size_t;
using Char = char;
using Char8 = char;
using UChar = unsigned char;
using UChar8 = unsigned char;
using Char16 = wchar_t;
// --==</alias>==--

// --==<support_macroses>==--
#define NWL_CSTR(anything) (#anything)
#define NWL_STR(anything) (std::string(anything))
#define NWL_STR_FORM(format, args);
#define NWL_STR_PART_L(str, symb) ( ( str.substr(0, str.rfind(symb) + 1) ).c_str() )
#define NWL_STR_PART_R(str, symb) ( ( str.substr(str.rfind(symb) + 1, str.size()) ).c_str() )
#define NWL_FNAME_APATH(path) ( NW_STR_PART_R(std::string(path), '\\') )
#define NWL_FDIR_APATH(path) ( NW_STR_PART_L(std::string(path), '\\') )
#define NWL_BIND_FN(func) (std::bind(&func, this, std::placeholders::_1))

#define NWL_XY_TO_X(x, y, w) (y * w + x)

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
	class NWL_API ADataRes;
	struct NWL_API AEvent;
	struct NWL_API WindowEvent;
	struct NWL_API MouseEvent;
	struct NWL_API KeyboardEvent;
}

#endif	// NWL_CORE_HPP