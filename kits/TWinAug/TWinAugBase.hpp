// Copyright (c) Orange Lee. Licensed under the MIT Licence.
// See the LICENCE file in the repository root for full licence text.

#pragma once

#if TKERNEL_WINVER > 0

#include "../TStdInclude.hpp"

// 继承该类后，编写名为 AugProc 的函数。
class TAugProcBase
{
	friend class TWindow;

	using AugProcType = std::function<void(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)>;
	std::vector<AugProcType> __pre_procs;
	std::vector<AugProcType> __post_procs;

protected:
	template<typename T>
	void append_pre_proc(T* _this)
	{
		__pre_procs.push_back(std::bind(&T::AugProc, _this,
			std::placeholders::_1, std::placeholders::_2,
			std::placeholders::_3, std::placeholders::_4));
	}
	template<typename T>
	void append_post_proc(T* _this)
	{
		__post_procs.push_back(std::bind(&T::AugProc, _this,
			std::placeholders::_1, std::placeholders::_2,
			std::placeholders::_3, std::placeholders::_4));
	}
};

#endif // TKERNEL_WINVER > 0