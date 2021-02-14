#ifndef NWL_PLATFORM_HPP
#define NWL_PLATFORM_HPP

#if (defined NWL_PLATFORM_WINDOWS)
#define NOMINMAX
#include <windows.h>
#include <commdlg.h>
#pragma comment(lib, "winmm.lib")
namespace NWL
{
	struct NativeWindow { HWND pHandle = NULL; inline operator HWND& () { return pHandle; } };
}
#endif	// NWL_PLATFORM_WINDOWS

#endif	// NWL_PLATFORM_HPP