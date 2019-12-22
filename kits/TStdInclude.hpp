// Copyright (c) Orange Lee. Licensed under the MIT Licence.
// See the LICENCE file in the repository root for full licence text.

#pragma once

#pragma warning(push)
#pragma warning(disable:4458)

// CRT
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cassert>
#include <climits>
#include <cctype>
#include <ctime>

// STL
#include <iostream>
#include <algorithm>
#include <array>
#include <vector>
#include <string>
#include <sstream>
#include <stack>
#include <queue>
#include <deque>
#include <map>
#include <set>
#include <bitset>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <random>
#include <stdexcept>
#include <typeinfo>
#include <thread>
#include <chrono>
#if _HAS_CXX17
#include <optional>
#include <filesystem>
#endif // _HAS_CXX17

#if TKERNEL_WINVER > 0

// Windows Base
#include <Windows.h>
#include <windowsx.h>
#include <tchar.h>

// Extra
#include <tlhelp32.h>
#include <commctrl.h>
#include <commdlg.h>
#include <shellapi.h> 
#include <shlobj.h>
#include <shldisp.h>
#include <Psapi.h>
#include <dwmapi.h>

// Graphics
#if TKERNEL_GDIPVER > 0

#if TKERNEL_GDIPVER == 11
#define GDIPVER 0x0110
#endif // TKERNEL_GDIPVER == 11

#include <gdiplus.h>

#endif // TKERNEL_WINVER > 0

#include <d2d1.h>
#include <d2d1_1.h>

// Common Control 6.0
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif

// link lib
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "version.lib")
#pragma comment(lib, "Psapi.lib")
#pragma comment(lib, "shlwapi")
#pragma comment(lib, "Msimg32.lib")
#pragma comment(lib, "comctl32.lib")
#pragma comment(lib, "shell32.lib")
#pragma comment(lib, "dwmapi.lib")
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "gdiplus.lib")

#endif // TKERNEL_WINVER > 0

#pragma warning(pop)