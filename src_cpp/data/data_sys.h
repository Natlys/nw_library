#ifndef NWL_DATA_SYSTEM_H
#define NWL_DATA_SYSTEM_H
#include <nwl_core.hpp>
#include <core/nwl_info.h>
#include <data/data_res.h>
namespace NWL
{
	/// DataSys static class
	class NWL_API DataSys
	{
	public:
		// --getters
		static inline const char* GetDirectory() { return &s_strDir[0]; }
		// --core_methods
		static void OnInit();
		static void OnQuit();
		// --dialogs
		static String DialogSave(const char* strFilter, Ptr pWindow);
		static String DialogLoad(const char* strFilter, Ptr pWindow);
		// --save_load
		static bool SaveFile(const char* strFPath, Ptr pData, Size szBytes);
		static bool LoadFile(const char* strFPath, Ptr pData, Size szBytes);
		static bool SaveFile(const char* strFPath, String& rData);
		static bool LoadFile(const char* strFPath, String& rData);
		static bool SaveFile(const char* strFPath, AInfo& rData);
		static bool LoadFile(const char* strFPath, AInfo& rData);
	private:
		static String s_strDir;
	};
}

#endif	// NWL_DATA_SYSTEM_H