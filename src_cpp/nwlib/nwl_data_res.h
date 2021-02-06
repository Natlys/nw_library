#ifndef NWL_DATA_RES_H
#define NWL_DATA_RES_H

#include <nwl_core.hpp>

#include <nwlib/nwl_memory.h>
#include <nwlib/nwl_file.h>
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
	protected:
		ADataRes(const char* strName, UInt32 unId);
	public:
		ADataRes(const ADataRes& rCpy) = delete;
		virtual ~ADataRes();

		// --getters
		inline UInt32 GetId() const { return m_unId; }
		inline const char* GetName() const { return &m_strName[0]; }
		
		// --setters
		virtual void SetName(const char* strName);

		// --core_methods
		virtual bool SaveF(const char* strFPath) = 0;
		virtual bool LoadF(const char* strFPath) = 0;
		
		// --operators
		void operator =(const ADataRes& rCpy) = delete;
		void operator delete(Ptr pBlock) = delete;
		void operator delete[](Ptr pBlock) = delete;
	protected:
		UInt32 m_unId;
		String m_strName;
	};
}
namespace NWL
{
	template<class DRType>
	class NWL_API TDataRes : public ADataRes
	{
		using DRs = DArray<DRType*>;
	protected:
		TDataRes(const char* strName) : ADataRes(strName, GetIdStack().GetFreeId()) { AddDataRes(static_cast<DRType&>(*this)); }
	public:
		virtual ~TDataRes() { RmvDataRes(GetId()); GetIdStack().SetFreeId(GetId()); }

		// --getters
		static inline DRs& GetStorage() { static DRs s_DRs; return s_DRs; }
		static inline DRType* GetDataRes(const char* strName);
		static inline DRType* GetDataRes(UInt32 unId);
		// --setters
		static inline void AddDataRes(DRType& rDataRes);
		static inline void RmvDataRes(const char* strName);
		static inline void RmvDataRes(UInt32 unId);
		// --core_methods
		virtual bool SaveF(const char* strFPath) = 0;
		virtual bool LoadF(const char* strFPath) = 0;
	protected:
		static inline IdStack& GetIdStack() { static IdStack s_idStack; return s_idStack; }
	};
	// --getters
	template <class DRType> inline DRType* TDataRes<DRType>::GetDataRes(UInt32 unId) {
		DRs<DRType>& s_DRs = GetStorage();
		if (s_DRs.size() <= unId) { return nullptr; }
		return s_DRs[unId];
	}
	template <class DRType> inline DRType* TDataRes<DRType>::GetDataRes(const char* strName) {
		auto& s_DRs = GetStorage();
		if (s_DRs.empty()) { return nullptr; }
		auto& itDR = std::find_if(s_DRs.begin(), s_DRs.end(),
			[=](DRType* pObj)->bool { if (pObj == nullptr) { return false; } return strcmp(&(pObj->GetName())[0], strName) == 0; });
		return itDR == s_DRs.end() ? *s_DRs.begin() : *itDR;
	}
	// --setters
	template <class DRType> inline void TDataRes<DRType>::AddDataRes(DRType& rDataRes) {
		auto& s_DRs = GetStorage();
		UInt32 unId = rDataRes.GetId();
		if (s_DRs.size() <= unId) { s_DRs.resize((unId + 1) * 2); }
		s_DRs[unId] = &rDataRes;
	}
	template <class DRType> inline void TDataRes<DRType>::RmvDataRes(const char* strName) {
		auto& s_DRs = GetStorage();
		if (s_DRs.empty()) { return; }
		auto& itDR = std::find_if(s_DRs.begin(), s_DRs.end(),
			[=](DRType* pObj)->bool { if (pObj == nullptr) { return false; } return strcmp(&(pObj->GetName())[0], strName) == 0; });
		if (itDR == s_DRs.end()) { return; }
		*itDR = nullptr;
	}
	template <class DRType> inline void TDataRes<DRType>::RmvDataRes(UInt32 unId) {
		auto& s_DRs = GetStorage();
		if (s_DRs.size() <= unId) { return; }
		s_DRs[unId] = nullptr;
	}
}
namespace NWL
{
	/// ImageInfo struct
	struct NWL_API ImageInfo
	{
	public:
		UByte* pClrData = nullptr;
		Int32 nWidth = 1, nHeight = 1, nDepth = 1, nChannels = 1;
	public:
		ImageInfo(UByte* pData = nullptr, Int32 nX = 1, Int32 nY = 1, Int32 nZ = 1) :
			pClrData(pData), nWidth(nX), nHeight(nY), nDepth(nZ), nChannels(1) {}
		// --getters
		inline Size GetDataSize() { return nChannels * nWidth * nHeight * nDepth; }
	};
	/// GMeshInfo struct
	struct NWL_API GMeshInfo
	{
	public:
		String strName;
		String strMtlName;
		DArray<Byte> vtxData;
		DArray<Byte> idxData;
		DArray<Byte> vtxDataBox;
	public:
	};
	/// GraphicalModelInfo struct
	struct NWL_API GModelInfo
	{
	public:
		String strName;
		DArray<GMeshInfo> Meshes;
	public:
	};
}
#endif // NWL_DATA_RES_H