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