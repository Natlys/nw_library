#ifndef NWL_IO_EXCEPTION_H
#define NWL_IO_EXCEPTION_H
#include <nwl_core.hpp>
#include <core/nwl_string.h>
#include <core/nwl_switch.h>

namespace NWL
{
	class NWL_API Exception
	{
	public:
		Exception(const char* strComment = "default", UInt32 unCode = ERC_DEFAULT, const char* strLoc = "default", UInt32 nLine = -1);
		// --getters
		inline const char* GetStr();
		inline const char* GetCom()		{ return &m_strComment[0]; }
		inline const char* GetLoc()		{ return &m_strLocation[0]; }
		inline UInt32 GetCode() const	{ return m_unCode; }
		inline UInt32 GetLine() const	{ return m_unLine; }
		// --operators
		std::ostream& operator<<(std::ostream& rStream);
		std::istream& operator>>(std::istream& rStream);
	private:
		String m_strComment;
		String m_strLocation;
		UInt32 m_unCode;
		UInt32 m_unLine;
	};
	std::ostream& operator<<(std::ostream& rStream, Exception& rExc);
	std::istream& operator>>(std::istream& rStream, Exception& rExc);
}
#if (defined NWL_PLATFORM_WINDOWS)
namespace NWL
{
	class NWL_API WinException : public Exception
	{
	public:
		WinException(const char* strInfo = "default", UInt32 nCode = ERC_DEFAULT, const char* strLoc = "default", UInt32 nLine = -1);
	};
}
#endif	// NWL_PLATFORM
#endif	// NWL_IO_EXCEPTION_H