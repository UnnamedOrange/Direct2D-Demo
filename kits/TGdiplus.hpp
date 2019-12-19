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

#if TKERNEL_WINVER > 0 && TKERNEL_GDIPVER > 0

#include "TStdInclude.hpp"

class TGdiplus final
{
	ULONG_PTR gdiplusToken{};
	BOOL isLoaded{};
	void Startup()
	{
		if (isLoaded) return;
		Gdiplus::GdiplusStartupInput gdiplusStartupInput;
		Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);
		isLoaded = TRUE;
	}
	TGdiplus() = default;

public:
	~TGdiplus()
	{
		if (gdiplusToken)
		{
			Gdiplus::GdiplusShutdown(gdiplusToken);
			gdiplusToken = NULL;
		}
	}

	// 在程序开始执行时调用该函数即可启用 GDIP。TGdiplus 将自动关闭 Gdiplus。
	static VOID EnableGdiplus()
	{
		static TGdiplus instance;
		instance.Startup();
	}
};

#endif // TKERNEL_WINVER > 0 && TKERNEL_GDIPVER > 0