#ifndef NWL_IO_EXCEPTION_H
#define NWL_IO_EXCEPTION_H

#include <nwl_core.hpp>
#include <core/nwl_string.h>

namespace NWL
{
	/// Abstract Exception class
	class NWL_API AException
	{
	protected:
		AException() { }
	public:
		virtual ~AException() { }
		// --getters
		virtual inline const char* GetStr() const { return "none"; }
		virtual inline const char* GetStrType() const { return "none"; }
		virtual inline UInt64 GetCode() const { return -1; }
	};
	/// Templated Exception class
	template <class EType>
	class NWL_API TException : public AException
	{
	public:
		TException() : AException() {}
		virtual ~TException() {}
		// --getters
		virtual inline const char* GetStr() const override { return NWL_CSTR(EType); }
		virtual inline const char* GetStrType() const override { return NWL_CSTR(EType); }
		virtual inline UInt64 GetCode() const override { return -1; }
	};
	/// Basic DefaultException class
	class NWL_API CodeException : public TException<CodeException>
	{
	public:
		CodeException(const char* strInfo, UInt64 unCode = -1, const char* strLoc = "none", UInt16 strLine = 0) :
			TException(),
			m_strInfo(&(std::string(strInfo) + std::string(strLoc) + std::to_string(strLine))[0]),
			m_unCode(unCode) { }
		virtual ~CodeException() { }
		// --getters
		virtual inline const char* GetStr() const override { return m_strInfo; }
		virtual inline UInt64 GetCode() const { return m_unCode; }
	private:
		const char* m_strInfo;
		UInt64 m_unCode;
	};
}

#endif	// NWL_IO_EXCEPTION_H