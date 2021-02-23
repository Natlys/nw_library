#ifndef NWL_DATA_SYSTEM_H
#define NWL_DATA_SYSTEM_H

#include <nwl_core.hpp>

#include <data/data_res.h>
#include <data/data_mesh.h>
#include <data/data_image.h>

namespace NWL
{
	/// DataSys static class
	class NWL_API DataSys
	{
	public:
		// --getters
		static inline const char* GetDirectory() { return &s_strRscDir[0]; }
		// --core_methods
		static void OnInit();
		static void OnQuit();

		static const char* FDialogSave(const char* strFilter, Ptr pWindow);
		static const char* FDialogLoad(const char* strFilter, Ptr pWindow);

		static bool SaveFData(const char* strFPath, void* pData, Size szBytes);
		static bool LoadFData(const char* strFPath, void* pData, Size szBytes);

		static bool SaveFString(const char* strFPath, const char* strSrc, Size szBytes);
		static bool LoadFString(const char* strFPath, String& strDest);

		static bool SaveFImage(const char* strFPath, Image& rImage);
		static bool LoadFImage(const char* strFPath, Image& rImage);
		static bool LoadFImageBmp(const char* strFPath, Image& rImage);
		static bool LoadFImagePng(const char* strFPath, Image& rImage);

		static bool SaveFMesh(const char* strFPath, GfxMeshInfo& rMesh);
		static bool LoadFMesh(const char* strFPath, GfxMeshInfo& rMesh);
		static bool LoadFMeshObj(const char* strFile, GfxMeshInfo& rMesh);
		static bool SaveFModel(const char* strFPath, GfxModelInfo& rModel);
		static bool LoadFModel(const char* strFPath, GfxModelInfo& rModel);
		static bool LoadFModelObj(const char* strFile, GfxModelInfo& rModel);
	private:
		static String s_strRscDir;
	};
}

#endif	// NWL_DATA_SYSTEM_H