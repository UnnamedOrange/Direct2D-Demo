// Copyright (c) Orange Lee. Licensed under the MIT Licence.
// See the LICENCE file in the repository root for full licence text.

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