#ifndef NWL_DATA_RES_H
#define NWL_DATA_RES_H

#include <nwl_core.hpp>

#include <ecs/ecs_entity.h>
#include <core/nwl_container.h>
#include <core/nwl_string.h>
#include <core/nwl_type.h>

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
		ADataRes(const char* strName, UInt32 tId) : m_strName("none"), m_tId(tId), m_drId(0) { SetName(strName); }
	public:
		ADataRes(const ADataRes& rCpy) = delete;
		virtual ~ADataRes() { }
		// --getters
		inline UInt32 GetDrId() const { return m_drId; }
		inline UInt32 GetTypeId() const { return m_tId; }
		inline const char* GetName() const { return &m_strName[0]; }
		// --setters
		virtual void SetName(const char* strName) { strcpy_s(&m_strName[0], 256, &strName[0]); }
		// --predicates
		template<class DType>
		inline bool IsOfType() { return TypeIndexator::Get<DType>() == GetTypeId(); }
		// --core_methods
		virtual bool SaveF(const char* strFPath) = 0;
		virtual bool LoadF(const char* strFPath) = 0;
	protected:
		UInt32 m_drId;
		UInt32 m_tId;
		Char m_strName[256];
	};
}
namespace NWL
{
	struct NWL_API BitMapInfo {
		struct {
			UInt16  nType = 0;
			Size    szData = 3;
			UInt16  nReserved1 = 0;
			UInt16  nReserved2 = 0;
			Size    szOffset = 54;
		}File;
		struct {
			Size    szData = 3;
			Int64   nWidth = 1;
			Int64   nHeight = 1;
			UInt16  nPlanes = 1;
			UInt16  nPxBits = 24;
			Size    szCompression = 0;
			Size    szImage = 3;
			Int64   nXppm = 0;          // vert resolution
			Int64   nYppm = 0;          // horz resolution
			UInt64  nClrUsed = 0;       // indexed pallete count
			UInt64  nClrImportant = 0;  // considered  as important colors
		}Data;
	};
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
		// --setters
		inline void SetPixel(UInt32 nX, UInt32 nY, UByte nR) {
			Size szCoord = NWL_XY_TO_X(nX * 1, nY * 1, nWidth);
			pClrData[szCoord++] = nR;
		}
		inline void SetPixel(UInt32 nX, UInt32 nY, UByte nR, UByte nG) {
			Size szCoord = NWL_XY_TO_X(nX * 2, nY * 2, nWidth);
			pClrData[szCoord++] = nR;
			pClrData[szCoord++] = nG;
		}
		inline void SetPixel(UInt32 nX, UInt32 nY, UByte nR, UByte nG, UByte nB) {
			Size szCoord = NWL_XY_TO_X(nX * 3, nY * 3, nWidth);
			pClrData[szCoord++] = nR;
			pClrData[szCoord++] = nG;
			pClrData[szCoord++] = nB;
		}
		inline void SetPixel(UInt32 nX, UInt32 nY, UByte nR, UByte nG, UByte nB, UByte nA) {
			Size szCoord = NWL_XY_TO_X(nX * 4, nY * 4, nWidth);
			pClrData[szCoord++] = nR;
			pClrData[szCoord++] = nG;
			pClrData[szCoord++] = nB;
			pClrData[szCoord++] = nA;
		}
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