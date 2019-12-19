// Copyright (c) 2018-2019 Orange Software
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once

#pragma warning(push)

#ifdef TKERNEL_DEV
#pragma warning(disable:4100) // 未引用的形参
#endif

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