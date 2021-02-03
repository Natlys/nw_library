#ifndef NWL_DATA_RES_H
#define NWL_DATA_RES_H

#include <nwl_core.hpp>

#include <utility/nwl_container.h>
#include <utility/nwl_id_stack.h>
#include <utility/nwl_string.h>
#include <utility/nwl_type.h>

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
		friend class DataSys;
	protected:
		ADataRes(const char* strName, UInt32 tId);
	public:
		ADataRes(const ADataRes& rCpy) = delete;
		virtual ~ADataRes();
		// --getters
		inline UInt32 GetId() const { return m_drId; }
		inline UInt32 GetTypeId() const { return m_tId; }
		inline const char* GetName() const { return &m_strName[0]; }
		// --setters
		virtual void SetName(const char* strName);
		// --predicates
		template<class DType>
		inline bool IsOfType() { return TypeIndexator::Get<DType>() == GetTypeId(); }
		// --operators
		void operator=(const ADataRes& rCpy) = delete;
		void operator delete(Ptr pBlock) = delete;
		void operator delete[](Ptr pBlock) = delete;
		// --core_methods
		virtual bool SaveF(const char* strFPath) = 0;
		virtual bool LoadF(const char* strFPath) = 0;
	protected:
		UInt32 m_drId;
		UInt32 m_tId;
		String m_strName;
	};
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