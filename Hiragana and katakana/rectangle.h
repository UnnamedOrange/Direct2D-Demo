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
		virtual void OnDraw(const draw_struct& ds)
		{
			auto [render_target, relative_x, relative_y] = ds;
			ID2D1SolidColorBrush* brush{};
			render_target->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Orange), &brush);
			render_target->FillRectangle(D2D1::RectF(relative_x + left, relative_y + top, relative_x + left + width, relative_y + top + height),
				brush);
			brush->Release();
		}
		virtual bool OnHitTest(int x, int y) { return false; }
	};
}