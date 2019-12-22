// Copyright (c) Orange Lee. Licensed under the MIT Licence.
// See the LICENCE file in the repository root for full licence text.

#pragma once

#include "pch.h"

#include "Utils/PerformanceCounter.hpp"

namespace D2DDemo::ProcessRing::Window
{
	class MainWindow : public TWindowNormal,
		public TWinAug::TDPI,
		public TWinAug::TWinSize
	{
		virtual LRESULT WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) override;
		void OnPaint(HWND hwnd);

	private:
		ID2D1HwndRenderTarget* pRenderTarget{};
		void CreateD2DRenderTarget();
		void ReleaseD2DRenderTarget();

	private:
		Utils::PerforamnceCounter time;
		std::deque<INT64> dq;
		void Paint();

	public:
		MainWindow();

	public:
		int PeekMessageLoop();
	};
}