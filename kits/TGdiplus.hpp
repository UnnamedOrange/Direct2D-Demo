// Copyright (c) Orange Lee. Licensed under the MIT Licence.
// See the LICENCE file in the repository root for full licence text.

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