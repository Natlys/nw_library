#ifndef NWL_IO_LOG_H
#define NWL_IO_LOG_H

#include <nwl_core.hpp>

#include <io/io_stream.h>
#include <core/nwl_string.h>

namespace NWL
{
	/// LogSystem static class
	class NWL_API LogSys
	{
	public:
		using ILog = StrStream;
		using OLog = OutStream;
	public:
		// --getters
		static inline ILog& GetILog() { return *s_piLog; }
		static inline OLog& GetOLog() { return *s_poLog; }
		// --setters
		static void OnInit();
		static void OnQuit();
		static void Update();
		static void SetOutput(OLog& routLog) { s_poLog = &routLog; }
		// --core_methods
		static void WriteInf(const char* strFormat, ...);
		static void WriteErr(Int32 nErrCode, const char* strFormat, ...);
		static void WriteWrn(const char* strFormat, ...);
	private:
		static ILog* s_piLog;
		static OLog* s_poLog;
	};
}
#endif // NWL_IO_LOG_H