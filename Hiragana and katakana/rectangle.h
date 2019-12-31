// Copyright (c) Orange Lee. Licensed under the MIT Licence.
// See the LICENCE file in the repository root for full licence text.

#pragma once

#include "pch.h"

#include "widget.h"

namespace D2DDemo::HiraganaAndKatakana::UI::Widget
{
	class rectangle : public widget
	{
	public:
		bool color_switch{};
		virtual void OnDraw(const draw_struct& ds) override
		{
			auto [render_target, relative_x, relative_y] = ds;
			ID2D1SolidColorBrush* brush{};
			render_target->CreateSolidColorBrush(D2D1::ColorF(color_switch ? D2D1::ColorF::AliceBlue : D2D1::ColorF::Orange), &brush);
			render_target->FillRectangle(D2D1::RectF(relative_x + left, relative_y + top, relative_x + left + width, relative_y + top + height),
				brush);
			brush->Release();
		}
		// virtual bool OnHitTest(int x, int y) { return false; }
		virtual bool OnClick(int x, int y) override
		{
			color_switch ^= 1;
			return true;
		}

	public:
		rectangle(int x = 0, int y = 0, int cx = 0, int cy = 0)
		{
			move(x, y);
			resize(cx, cy);
		}
	};
}