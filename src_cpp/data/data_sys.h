#ifndef NWL_DATA_SYSTEM_H
#define NWL_DATA_SYSTEM_H

#include <nwl_core.hpp>

#include <data/data_res.h>
#include <ecs/ecs_entity.h>
#include <core/nwl_container.h>
#include <io/io_stream.h>
#include <io/io_exception.h>
#include <core/nwl_string.h>

namespace NWL
{
	/// DataSys static class
	class NWL_API DataSys
	{
	public:
		// --getters
		static inline const char* GetDirectory() { return &s_strRscDir[0]; }
		// --core_methods
		static void OnInit() { }
		static void OnQuit() { }

		static String FDialogSave(const char* strFilter, Ptr pWindow);
		static String FDialogLoad(const char* strFilter, Ptr pWindow);

		static bool SaveFData(const char* strFPath, void* pData, Size szBytes);
		static bool SaveFData(const char* strDir, const char* strName, const char* strFormat,
			void* pData, Size szBytes);
		static bool LoadFData(const char* strFPath, void* pData, Size szBytes);
		static bool LoadFData(const char* strDir, const char* strName, const char* strFormat,
			void* pData, Size szBytes);

		static bool SaveFString(const char* strFPath, const char* strSrc, Size szBytes);
		static bool LoadFString(const char* strFPath, String& strDest);

		static bool SaveFImage(const char* strFPath, ImageInfo& rImage);
		static bool LoadFImage(const char* strFPath, ImageInfo& rImage);
		static bool LoadFImageBmp(const char* strFPath, ImageInfo& rImage);

		static bool SaveFMesh(const char* strFPath, GMeshInfo& rMesh);
		static bool LoadFMesh(const char* strFPath, GMeshInfo& rMesh);
		static bool SaveFModel(const char* strFPath, GModelInfo& rModel);
		static bool LoadFModel(const char* strFPath, GModelInfo& rModel);
	private:
		static String s_strRscDir;
	private:
		static inline IdStack& GetIdStack() { static IdStack s_idStack; return s_idStack; }

		static inline bool LoadFMeshObj(const char* strFile, GMeshInfo& rMesh);
		static inline bool LoadFModelObj(const char* strFile, GModelInfo& rModel);
	};
}

#endif	// NWL_DATA_SYSTEM_H