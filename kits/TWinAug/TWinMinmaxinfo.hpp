// Copyright (c) Orange Lee. Licensed under the MIT Licence.
// See the LICENCE file in the repository root for full licence text.

#pragma once

#include "TWinAugBase.hpp"

namespace TWinAug
{
	// 限制窗口的最小大小
	class TWinMinmaxinfo : virtual public TAugProcBase
	{
		virtual POINT _QueryMinTrackSize() = 0;

	public:
		void AugProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
		{
			switch (message)
			{
			case WM_GETMINMAXINFO:
				HANDLE_WM_GETMINMAXINFO(hwnd, wParam, lParam,
					[this](HWND hwnd, LPMINMAXINFO lpMinMaxInfo)
					{
						lpMinMaxInfo->ptMinTrackSize = _QueryMinTrackSize();
					});
			}
		}

	public:
		TWinMinmaxinfo()
		{
			append_pre_proc(this);
		}
	};
}