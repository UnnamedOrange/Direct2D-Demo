﻿// Copyright (c) Orange Lee. Licensed under the MIT Licence.
// See the LICENCE file in the repository root for full licence text.

#pragma once

#include "pch.h"

#include "widget.h"
#include "root.h"

namespace D2DDemo::HiraganaAndKatakana::Window
{
	class MainWindow : public TWindowNormal,
		public TWinAug::TDPI,
		public TWinAug::TWinSize
	{
		virtual LRESULT WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) override;
		void OnPaint(HWND hwnd);

	private:
		UI::Widget::root ui;
		ID2D1HwndRenderTarget* pRenderTarget{};
		void CreateD2DRenderTarget();
		void ReleaseD2DRenderTarget();

		void draw()
		{
			InvalidateRect(GetHwnd(), nullptr, false);
		}
		void Paint(ID2D1RenderTarget* render_target);

	public:
		MainWindow();

	public:
		int PeekMessageLoop();
	};
}