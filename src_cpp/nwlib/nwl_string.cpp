#include "nwl_string.h"

namespace NWL
{
	inline UInt32 StrLen(const char* cString) {
		UInt32 unCounter = 0;
		while (cString[unCounter] != '\0') unCounter++;
		return unCounter;
	}

	inline Int32 StrFindL(const char* cSource, const char cFind) {
		UInt32 unCounter = 0;
		while (cSource[unCounter] != '\0')
		{
			unCounter++;
			if (cSource[unCounter] == cFind) return unCounter;
		}
		return -1;
	}
	inline Int32 StrFindR(const char* cSource, const char cFind) {
		Int32 nCounter = StrLen(cSource);
		while (nCounter != -1)
		{
			nCounter--;
			if (cSource[nCounter] == cFind) return nCounter;
		}
		return -1;
	}
	const char* GetStringPart(const char* cSource, UInt32 unBegin) {
		return "";
	}
	const char* GetStringPart(const char* cSource, UInt32 unBegin, UInt32 unEnd) {
		char* pStrPart = nullptr;
		Size szChars = unBegin < unEnd ? unEnd - unBegin : unBegin - unEnd;
		pStrPart = new char[szChars];
		for (UInt32 nPos = unBegin; nPos != unEnd; nPos--)
		{
			//
		}
		const char* strRes = pStrPart;
		delete pStrPart;
		return strRes;
	}
}