#ifndef NWL_DATA_RES_H
#define NWL_DATA_RES_H

#include <nwl_core.hpp>
#include <core/nwl_info.h>
#include <core/nwl_string.h>
#include <memory/mem_sys.h>

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
	class NWL_API ADataRes : public AMemUser
	{
		friend class DataSys;
	protected:
		ADataRes() : m_strName("none") { }
		ADataRes(const char* strName) : m_strName("none") { SetName(strName); }
	public:
		virtual ~ADataRes() { }
		// --getters
		inline const char* GetName() const { return &m_strName[0]; }
		// --setters
		virtual void SetName(const char* strName) { m_strName = strName; }
		// --predicates
		template<class DType>
		inline bool IsOfType() { return TypeIndexator::GetId<DType>() == GetTypeId(); }
		// --core_methods
		virtual bool SaveF(const char* strFPath) = 0;
		virtual bool LoadF(const char* strFPath) = 0;
	protected:
		String m_strName;
	};
}

#endif // NWL_DATA_RES_H