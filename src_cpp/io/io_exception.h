#ifndef NWL_IO_EXCEPTION_H
#define NWL_IO_EXCEPTION_H

#include <nwl_core.hpp>
#include <core/nwl_string.h>
#include <io/io_stream.h>

namespace NWL
{
	class NWL_API Exception
	{
	public:
		Exception(const char* strInfo, UInt32 nCode = NWL_ERR_DEFAULT, const char* strLoc = "none", UInt32 nLine = -1);
		virtual ~Exception();
		// --getters
		virtual inline const char* GetStr() { return m_strInfo; }
		virtual inline UInt32 GetCode() { return m_unErrCode; }
		// --operators
		inline OStream& operator<<(OStream& rStream) { return rStream << &m_strInfo[0]; }
	private:
		const char* m_strInfo;
		UInt32 m_unErrCode;
	};
	inline OStream& operator<<(OStream& rStream, Exception& rExc) { return rExc.operator<<(rStream); }
}

#endif	// NWL_IO_EXCEPTION_H