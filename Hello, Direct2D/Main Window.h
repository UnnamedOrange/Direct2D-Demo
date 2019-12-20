// Copyright (c) Orange Lee. Licensed under the MIT Licence.
// See the LICENCE file in the repository root for full licence text.

#pragma once

#include "pch.h"

namespace D2DDemo::HelloDirect2D::Window
{
	class MainWindow : public TWindowNormal,
		public TWinAug::TDPI,
		public TWinAug::TWinSize
	{
		virtual LRESULT WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) override;

	private:
		ID2D1HwndRenderTarget* pRenderTarget{};
		void CreateD2DRenderTarget();
		void ReleaseD2DRenderTarget();

	private:
		void DrawRectangle();

	public:
		MainWindow();
	};
}