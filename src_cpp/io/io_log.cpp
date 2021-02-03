#include <nwl_pch.hpp>
#include "io_log.h"

namespace NWL
{
	// --==<core_methods>==--
	String LogSys::MakeFormatStr(const char* strFormat, va_list& valArgs)
	{
		String strProc;		// string for processing
		Size nLen = strlen(strFormat);	// strFormat length
		Size nCurr = 0;						// current position in the strFormat
		std::stringstream strProcStream, strResStream;

		strProcStream << strFormat;							// strFormat will be read via strStream

		while (!strProcStream.eof()) {		// read the format before one of '{' and append what is read
			std::getline(strProcStream, strProc, '{');
			nCurr += strProc.size();
			strResStream << strProc;
			if (nCurr < nLen && strFormat[nCurr] != '%') {		// Next can be %{ or '\0' -> then we write simple string
				std::getline(strProcStream, strProc, '}');
				nCurr += strProc.size();
				if (strProc == "int") {
					strResStream << va_arg(valArgs, Int32);
				}
				else if (strProc == "flt") {
					strResStream << va_arg(valArgs, Float64);
				}
				else if (strProc == "chr") {
					strResStream << va_arg(valArgs, char);
				}
				else if (strProc == "str") {
					strResStream << va_arg(valArgs, const char*);
				}
				else {	// No type found - error
					return strResStream.str();
				}
			}
			else {			// {{ is found - we can read further
				strResStream << strProc;
			}
		}

		return strResStream.str();
	}
	/// Read the formatted string like "some string {typ[:count[:delim]]}"
	void LogSys::WriteStr(const char* strFormat, ...)
	{
		va_list valArgs;					// all variadic arguments in ... will be read via this list
		va_start(valArgs, strFormat);	// the pointer to ... arguments is after strFormat
		GetLogOut() << &MakeFormatStr(strFormat, valArgs)[0] << '\n';
		va_end(valArgs);					// Essentialy close the list
	}
	void LogSys::WriteFile(void* pFile, const char* strFormat, ...)
	{
	}
	void LogSys::WriteErrStr(Int32 nErrCode, const char* strFormat, ...)
	{
		va_list valArgs;					// all variadic arguments in ... will be read via this list
		va_start(valArgs, strFormat);	// the pointer to ... arguments is after strFormat
		GetLogOut() << "ERROR::CODE_" << nErrCode << '\n';
		GetLogOut() << "ERROR::MESSAGE_" << &MakeFormatStr(strFormat, valArgs)[0] << '\n';
		NWL_BREAK();
		va_end(valArgs);					// Essentialy close the list
	}
	// --==</core_methods>==--
}