#include <nwl_pch.hpp>
#include "io_log.h"

NWL::LogSys::ILog* NWL::LogSys::s_piLog = nullptr;
NWL::LogSys::OLog* NWL::LogSys::s_poLog = nullptr;

namespace NWL
{
	// --==<core_methods>==--
	void LogSys::OnInit()
	{
		if (s_piLog != nullptr) { return; }
		s_piLog = new ILog();
		s_poLog = &std::cout;
	}
	void LogSys::OnQuit()
	{
		if (s_piLog == nullptr) { return; }
		delete s_piLog;
		s_piLog = nullptr;
		s_poLog = nullptr;
	}
	void LogSys::Update()
	{
		if (GetILog().eof()) { return; }
		GetOLog() << GetILog().rdbuf();
		GetILog().clear();
	}
	void LogSys::WriteInf(const char* strFormat, ...)
	{
		va_list valArgs;
		va_start(valArgs, strFormat);
		GetILog() << "--==<log_info>==--" << std::endl <<
			"::message:" << &StrGetFormatVa(strFormat, valArgs)[0] << std::endl <<
			"--==</log_info>==--" << std::endl;
		va_end(valArgs);
	}
	void LogSys::WriteWrn(const char* strFormat, ...)
	{
		va_list valArgs;
		va_start(valArgs, strFormat);
		GetILog() << "--==<log_warning>==--" << std::endl <<
			"::message:" << &StrGetFormatVa(strFormat, valArgs)[0] << std::endl <<
			"--==</log_warning>==--" << std::endl;
		va_end(valArgs);
		NWL_BREAK();
	}
	void LogSys::WriteErr(Int32 nErrCode, const char* strFormat, ...)
	{
		va_list valArgs;
		va_start(valArgs, strFormat);
		GetILog() << "--==<log_error>==--" << std::endl <<
			"code:" << nErrCode << std::endl <<
			"::message:" << &StrGetFormatVa(strFormat, valArgs)[0] << std::endl <<
			"--==</log_error>==--" << std::endl;
		va_end(valArgs);
		NWL_BREAK();
	}
	// --==</core_methods>==--
}