#ifndef NWL_PLATFORM_HPP
#define NWL_PLATFORM_HPP

#if (defined NWL_PLATFORM_WINDOWS)
#define NOMINMAX
#include <windows.h>
#include <commdlg.h>
#include <tchar.h>
#pragma comment(lib, "winmm.lib")
#endif	// NWL_PLATFORM_WINDOWS

#endif	// NWL_PLATFORM_HPP