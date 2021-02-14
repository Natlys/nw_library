#ifndef NWL_DATA_SYSTEM_H
#define NWL_DATA_SYSTEM_H

#include <nwl_core.hpp>

#include <data/data_res.h>
#include <io/io_stream.h>
#include <core/nwl_container.h>
#include <core/nwl_string.h>

namespace NWL
{
	/// DataSys static class
	class NWL_API DataSys
	{
	public:
		using DRStorage = HashMap<UInt32, RefKeeper<ADataRes>>;
		template<class DRType>
		using TDRStorage = HashMap<UInt32, DRType*>;
	public:
		// --getters
		static inline const char* GetDirectory() { return &s_strRscDir[0]; }
		static inline DRStorage& GetStorage();
		static inline RefKeeper<ADataRes>* GetDR(UInt32 unId);
		static inline RefKeeper<ADataRes>* GetDR(const char* strName);
		template<class DRType> static inline TDRStorage<DRType>& GetStorage();
		template<class DRType> static inline DRType* GetDR(UInt32 unId);
		template<class DRType> static inline DRType* GetDR(const char* strName);
		// --setters
		template<class DRType, typename ... Args>
		static inline UInt32 NewDR(Args ... Arguments);
		template<class DRType>
		static inline void DelDR(UInt32 unId);
		template<class DRType>
		static inline void DelDR(const char* strName);
		template<class DRType>
		static inline void AddDR(DRType& rDataRes);
		template<class DRType>
		static inline void RmvDR(UInt32 unId);
		template<class DRType>
		static inline void RmvDR(const char* strName);
		// --core_methods
		static void OnInit() { }
		static void OnQuit() { GetStorage().clear(); }

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
	// --getters
	inline DataSys::DRStorage& DataSys::GetStorage() { static DRStorage s_Drs; return s_Drs; }
	inline RefKeeper<ADataRes>* DataSys::GetDR(UInt32 unId) {
		auto& s_Drs = GetStorage();
		auto& itDr = s_Drs.find(unId);
		return itDr == s_Drs.end() ? nullptr : &itDr->second;
	}
	inline RefKeeper<ADataRes>* DataSys::GetDR(const char* strName) {
		auto& s_Drs = GetStorage();
		for (auto& itDr : s_Drs) {
			if (strcmp(itDr.second->GetName(), strName) == 0) { return &itDr.second; }
		}
		return nullptr;
	}
	template<class DRType> inline DataSys::TDRStorage<DRType>& DataSys::GetStorage() { static TDRStorage<DRType> s_TDrs; return s_TDrs; }
	template<class DRType> inline DRType* DataSys::GetDR(UInt32 unId) {
		auto& s_Drs = GetStorage<DRType>();
		auto& itDr = s_Drs.find(unId);
		return itDr == s_Drs.end() ? nullptr : itDr->second;
	}
	template<class DRType> inline DRType* DataSys::GetDR(const char* strName) {
		auto& s_Drs = GetStorage<DRType>();
		for (auto& itDr : s_Drs) {
			if (strcmp(itDr.second->GetName(), strName) == 0) { return itDr.second; }
		}
		return nullptr;
	}
	// --setters
	template<class DRType, typename ... Args>
	inline UInt32 DataSys::NewDR(Args ... Arguments) {
		auto& s_Drs = GetStorage();
		UInt32 drId = GetIdStack().GetFreeId();
		s_Drs[drId].MakeRef<DRType>(Arguments...);
		s_Drs[drId]->m_drId = drId;
		GetStorage<DRType>()[drId] = s_Drs[drId].GetRef<DRType>();
		return drId;
	}
	template<class DRType>
	inline void DataSys::DelDR(UInt32 unId) {
		auto& s_Drs = GetStorage();
		auto& itDr = s_Drs.find(unId);
		if (itDr == s_Drs.end()) { return; }
		if (itDr.second->GetTypeId() != TypeIndexator::Get<DRType>()) { return; }
		s_Drs.erase(itDr->first);
		GetStorage<DRType>().erase(itDr->first);
		GetIdStack().SetFreeId(itDr->first);
	}
	template<class DRType>
	inline void DataSys::DelDR(const char* strName) {
		for (auto& itDr : GetStorage()) {
			if (strcmp(itDr.second->GetName(), strName) == 0) {
				if (itDr.second->GetTypeId() == TypeIndexator::Get<DRType>()) {
					GetStorage().erase(itDr.first);
					GetStorage<DRType>().erase(itDr.first);
					GetIdStack().SetFreeId(itDr.first);
				}
			}
		}
	}
	template<class DRType>
	inline void DataSys::AddDR(DRType& rDataRes) {
		auto& s_Drs = GetStorage<DRType>();
		s_Drs[rDataRes.GetId()] = &rDataRes;
	}
	template<class DRType>
	inline void DataSys::RmvDR(UInt32 unId) {
		auto& s_Drs = GetStorage<DRType>();
		auto& itDr = s_Drs.find(unId);
		if (itDr == s_Drs.end()) { return; }
		s_Drs.erase(itDr);
	}
	template<class DRType>
	inline void DataSys::RmvDR(const char* strName) {
		auto& s_Drs = GetStorage<DRType>();
		for (auto& itDr : s_Drs) {
			if (strcmp(itDr.second->GetName(), strName) == 0) {
				s_Drs.erase(itDr.first);
			}
		}
	}
}
namespace NWL
{
	/// Templated DataResource class
	template<class DType>
	class NWL_API TDataRes : public ADataRes
	{
	protected:
		TDataRes(const char* strName) :
			ADataRes(strName, TypeIndexator::Get<DType>()) { /*DataSys::AddDR<DType>(static_cast<DType&>(*this));*/ }
		virtual ~TDataRes() { DataSys::RmvDR<DType>(GetId()); }
	public:
		virtual bool SaveF(const char* strFName) override { return true; }
		virtual bool LoadF(const char* strFName) override { return true; }
	};
}

#endif	// NWL_DATA_SYSTEM_H