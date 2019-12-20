// Copyright (c) Orange Lee. Licensed under the MIT Licence.
// See the LICENCE file in the repository root for full licence text.

#pragma once

#if TKERNEL_WINVER >= 1607

#include "TWinAugBase.hpp"

namespace TWinAug
{
	// 自动更新 dpi 参数，自动更新窗口大小
	class TDPI : virtual public TAugProcBase
	{
		double __dpi{};

	public:
		void AugProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
		{
			switch (message)
			{
			case WM_NCCREATE:
			case WM_INITDIALOG:
			case WM_DPICHANGED_BEFOREPARENT:
			{
				__dpi = static_cast<double>(GetDpiForWindow(hwnd)) / USER_DEFAULT_SCREEN_DPI;
				break;
			}
			case WM_DPICHANGED:
			{
				__dpi = static_cast<double>(HIWORD(wParam)) / USER_DEFAULT_SCREEN_DPI;

				RECT* const prcNewWindow = (RECT*)lParam;
				SetWindowPos(hwnd,
					NULL,
					prcNewWindow->left,
					prcNewWindow->top,
					prcNewWindow->right - prcNewWindow->left,
					prcNewWindow->bottom - prcNewWindow->top,
					SWP_NOZORDER | SWP_NOACTIVATE);
				break;
			}
			}
		}

	public:
		const double& dpi{ __dpi };

	public:
		TDPI()
		{
			append_pre_proc(this);
		}
	};
}

#endif // TKERNEL_WINVER >= 1607