#ifndef NWL_IO_LOG_H
#define NWL_IO_LOG_H

#include <nwl_core.hpp>

#include <utility/nwl_string.h>
#include <io/io_stream.h>

namespace NWL
{
	/// LogSystem static class
	/// Descritpion:
	/// -- The core debugger which helps to write messages and manage errors
	/// -- Main methods are "WriteF" and "WriteErrF" for formatted logging
	/// -- It can save logs in files, print the information on the screen(in the console for now)
	/// -- Format is described further
	/// -- For now 20.12.2020: only WriteF and WriteErrF
	/// -- I also can implement some exception which will report LogSystem about own error code
	/// Interface:
	/// -> Initialize the system
	/// -> WriteF to use formatted Logging.
	/// ==| The first argument is a format which describes how further arguments will be written
	/// ==| "{}" means that some symbols inside must reference some number further in arguments
	/// ==| In the curly brackets must be at least one first character - the type of argument
	/// ==| With ":" after the character we can assign, how much arguments follows
	/// ==| It is also possible to add second ":" to set a character-divisor which will be between args
	/// ==| Example: WriteF("Some message for {s:2:_}", "Formatted", "Logging"); -> Some Message for Formatted_Logging
	/// ==| For now only {t} format is supported
	class NWL_API LogSys
	{
	public:
		using LogIn = InStream;
		using LogOut = OutStream;
		using LogErr = OutStream;
		using LogStr = StrStream;
	public:
		// --getters
		static inline LogIn& GetLogIn() { return std::cin; }
		static inline LogOut& GetLogOut() { return std::cout; }
		static inline LogErr& GetLogErr() { return std::cerr; }
		static inline LogStr& GetLogStr() { static LogStr s_LogStr; return s_LogStr; }
		// --setters

		// --core_methods
		static String MakeFormatStr(const char* strFormat, va_list& vaList);
		static void WriteStr(const char* strFormat, ...);
		static void WriteFile(void* pFile, const char* strFormat, ...);
		static void WriteErrStr(Int32 nErrCode, const char* strFormat, ...);
	};
}

#endif // NWL_IO_LOG_H

//
///// FormatToken struct
///// Description:
///// -- Represents some value of any type for formatted writting
///// -- cIndicator is a character which helps to find that some character means this token
///// -- cDivisor is a character which is set between tokens
///// -- ftValue is an actual value representation for the token
//template<typename FTType> struct FToken
//{
//	FTType ftValue = FTType();
//	static const char* cIndicator;
//};
//const char* FToken<Int32>::cIndicator = "int";
//const char* FToken<float>::cIndicator = "flt";
//const char* FToken<double>::cIndicator = "dbl";
//const char* FToken<const char*>::cIndicator = "cst";
//const char* FToken<String>::cIndicator = "str";
///// LogParams struct
///// Description:
///// -- This is just a bunch of settings for LogSys
//enum LogFlags : UInt32 {
//	LF_WRITE_HEADER_LOGGER = 1 << 0,
//	LF_WRITE_LOC_DIR = 1 << 1, LF_WRITE_LOC_FILE = 1 << 2, LF_WRITE_LOC_LINE = 1 << 3
//};