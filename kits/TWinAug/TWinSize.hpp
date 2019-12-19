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

#include "TWinAugBase.hpp"

namespace TWinAug
{
	// 自动更新窗口客户区大小
	class TWinSize : virtual public TAugProcBase
	{
		int __cx{};
		int __cy{};

	public:
		void AugProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
		{
			switch (message)
			{
			case WM_NCCREATE:
			case WM_INITDIALOG:
			{
				RECT rect;
				GetClientRect(hwnd, &rect);
				__cx = rect.right - rect.left;
				__cy = rect.bottom - rect.top;
				break;
			}
			case WM_SIZE:
				HANDLE_WM_SIZE(hwnd, wParam, lParam,
					[this](HWND hwnd, UINT state, int cx, int cy)
					{
						__cx = cx;
						__cy = cy;
					});
			}
		}

	public:
		const int& width{ __cx };
		const int& height{ __cy };

	public:
		TWinSize()
		{
			append_pre_proc(this);
		}
	};
}