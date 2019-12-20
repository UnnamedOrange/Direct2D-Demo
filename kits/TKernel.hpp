// Copyright (c) Orange Lee. Licensed under the MIT Licence.
// See the LICENCE file in the repository root for full licence text.

#pragma once

#pragma warning(push)

#ifndef TKERNEL_WINVER
// 对于 Windows 10，请按年份-月份指定版本；对于 Windows 10 以前版本，请使用 7、8；对于不依赖 Windows 的程序，请使用 0
#define TKERNEL_WINVER 1903
#endif // TKERNEL_WINVER

#if TKERNEL_WINVER > 0
#ifndef TKERNEL_GDIPVER
// 对于 GDIP 1.0，请使用 10；对于 GDIP 1.1，请使用 11；对于不使用 GDIP 的程序，请使用 0
#define TKERNEL_GDIPVER 11
#endif // TKERNEL_GDIPVER
#endif // TKERNEL_WINVER

#include "TStdInclude.hpp"
#include "TSmartObject.hpp"
#include "TGdiplus.hpp"
#include "TApplication.hpp"
#include "TWindow.hpp"

#pragma warning(pop)