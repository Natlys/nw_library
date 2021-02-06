#include "nwl_string.h"

namespace NWL
{
	Int32 StrFindL(const char* strSource, char cFind) { return 0; }
	Int32 StrFindR(const char* strSource, char cFind) { return 0; }
	const char* SubStr(const char* strSource, UInt32 unBeg) { return ""; }
	const char* SubStr(const char* strSource, UInt32 unBeg, UInt32 unEnd) {
		char* pStrPart = nullptr;
		Size szChars = unBeg < unEnd ? unEnd - unBeg : unBeg - unEnd;
		pStrPart = new char[szChars];
		for (UInt32 nPos = unBeg; nPos != unEnd; nPos--) { }
		const char* strRes = pStrPart;
		delete[] pStrPart;
		return strRes;
	}

	const char* SubStrDelimR(const char* strSource, char cDelim, Int32 nStepFromDelim) {
		Char strBuf[128]{ 0 };
		Size nLen = strlen(strSource);
		Size nDel = nLen;
		while (strSource[--nDel] != cDelim) { if (nDel == 0) { return "error"; } }
		for (Size ic = nDel + nStepFromDelim, ibuf = 0; ic < nLen && ibuf < 128; ic++, ibuf++) { strBuf[ibuf] = strSource[ic]; }
		return &strBuf[0];
	}
}