#ifndef NWL_CODE_RES_H
#define NWL_CODE_RES_H

#include <nwl_core.hpp>
#include <nwl_data.hpp>

#include <core/nwl_string.h>

namespace NWL
{
	/// Abstract CodeChunk class
	/// Description:
	/// -- For classes which can handle some source code and compile that
	/// -- Scripts and shaders need to be edited, loaded, saved and compiled.
	class NWL_API ACodeRes : public TDataRes<ACodeRes>
	{
	public:
		ACodeRes(const char* strName);
		virtual ~ACodeRes();
		// --getters
		inline const char* GetCode() { return &m_strCode[0]; }
		// --setters
		inline void SetCode(const char* strCode) { m_strCode = strCode; }
		// --core_methods
		virtual bool Compile() = 0;
	protected:
		String m_strCode;
	};
}

#endif	// NWL_CODE_RES_H