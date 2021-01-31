#ifndef NWL_DATA_RES_H
#define NWL_DATA_RES_H

#include <nwl_core.hpp>

#include <nwlib/nwl_string.h>
#include <nwlib/nwl_id_stack.h>

namespace NWL
{
	/// Abstract DataResource class
	/// Interface:
	/// -> Derrive any class you want from the ADataRes class
	/// -> Implement Save() and Load() methods
	/// Description:
	/// -- Every object in the engine can be saved in a binary file or some format
	/// -- Class which is inherit of ADataRes can be: Saved | Loaded
	/// -- Everything we need - save/load methods implementation for this
	class NWL_API ADataRes
	{
	public:
		using ADRs = HashMap<UInt32, ADataRes*>;
		template <class DRType> using DRs = HashMap<UInt32, DRType*>;
	protected:
		ADataRes(const char* strName, UInt32 unId);
	public:
		ADataRes(const char* strName);
		ADataRes(const ADataRes& rDataRes) = delete;
		virtual ~ADataRes();

		// --getters
		inline UInt32 GetId() const { return m_unId; }
		inline const char* GetName() const { return &m_strName[0]; }
		
		// --setters
		virtual void SetName(const char* strName);

		// --core_methods
		virtual bool SaveF(const char* strFPath) = 0;
		virtual bool LoadF(const char* strFPath) = 0;

		static inline ADRs& GetADataResources() { return s_ADRs; }
		static inline ADataRes* GetADataRes(UInt32 unId);

		template <class DRType> static inline DRs<DRType>& GetDataResources() { static DRs<DRType> s_DRs; return s_DRs; }
		template <class DRType> static inline DRType* GetDataRes(UInt32 unId);
		template <class DRType> static inline DRType* GetDataRes(const char* strName);
		// --setters
		static void AddADataRes(ADataRes* pDataRes);
		static void RmvADataRes(UInt32 unId);

		template <class DRType> static inline void AddDataRes(DRType* pDataRes);
		template <class DRType> static inline void RmvDataRes(UInt32 unId);
		template <class DRType> static inline void RmvDataRes(const char* strName);
		// --operators
		void operator delete(Ptr pBlock) = delete;
		void operator delete[](Ptr pBlock) = delete;
	protected:
		UInt32 m_unId;
		String m_strName;
		String m_strDir;
	private:
		static IdStack s_IdStack;
		static ADRs s_ADRs;
	};
	// --implementation
	inline ADataRes* ADataRes::GetADataRes(UInt32 unId) {
		if (s_ADRs.empty()) { return nullptr; }
		ADRs::iterator itDR = s_ADRs.find(unId);
		return itDR == s_ADRs.end() ? nullptr : itDR->second;
	}
	template <class DRType> inline DRType* ADataRes::GetDataRes(UInt32 unId) {
		DRs<DRType>& s_DRs = GetDataResources<DRType>();
		if (s_DRs.empty()) { return nullptr; }
		DRs<DRType>::iterator itDR = s_DRs.find(unId);
		return itDR == s_DRs.end() ? nullptr : itDR->second;
	}
	template <class DRType> inline DRType* ADataRes::GetDataRes(const char* strName) {
		DRs<DRType>& s_DRs = GetDataResources<DRType>();
		if (s_DRs.empty()) { return nullptr; }
		DRs<DRType>::iterator itDR = std::find_if(s_DRs.begin(), s_DRs.end(),
			[=](std::pair<const UInt32, DRType*>& rObj)->bool { return strcmp(&rObj.second->GetName()[0], strName) == 0; });
		return itDR == s_DRs.end() ? s_DRs.begin()->second : itDR->second;
	}
	template <class DRType> inline void ADataRes::AddDataRes(DRType* pDataRes) {
		if (pDataRes == nullptr) { return; }
		GetDataResources<DRType>()[pDataRes->GetId()] = (pDataRes);
	}
	template <class DRType> inline void ADataRes::RmvDataRes(const char* strName) {
		DRs<DRType>& s_DRs = GetDataResources<DRType>();
		if (s_DRs.empty()) { return; }
		DRs<DRType>::iterator itDR = std::find_if(s_DRs.begin(), s_DRs.end(),
			[=](std::pair<const UInt32, DRType*>& rObj)->bool { return strcmp(&rObj.second->GetName()[0], strName) == 0; });
		if (itDR == s_DRs.end()) { return; }
		s_DRs.erase(itDR);
	}
	template <class DRType> inline void ADataRes::RmvDataRes(UInt32 unId) {
		DRs<DRType>& s_DRs = GetDataResources<DRType>();
		if (s_DRs.empty()) { return; }
		DRs<DRType>::iterator itDR = s_DRs.find(unId);
		if (itDR == s_DRs.end()) { return; }
		s_DRs.erase(itDR);
	}
}

#endif // NW_DATA_RES_H