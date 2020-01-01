// Copyright (c) Orange Lee. Licensed under the MIT Licence.
// See the LICENCE file in the repository root for full licence text.

#pragma once

#include "pch.h"

#include "widget.h"
#include "main.h"

namespace D2DDemo::HiraganaAndKatakana::UI::Widget
{
	class text : public widget
	{
	public:
		std::wstring content;

		IDWriteTextFormat* text_format{};

		virtual void OnDraw(const draw_struct& ds) override
		{
			ID2D1SolidColorBrush* brush;
			ds.render_target->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &brush);
			ds.render_target->DrawTextW(content.c_str(), content.length(), text_format,
				D2D1::RectF(left + ds.relative_x, top + ds.relative_y, left + ds.relative_x + width, top + ds.relative_y + height),
				brush);
			brush->Release();
		}
		virtual bool OnHitTest(int x, int y) { return false; }

	public:
		text(int x, int y, int cx, int cy, const std::wstring& content = L"") :content(content)
		{
			move(x, y);
			resize(cx, cy);
			Main::App().pDFactory->CreateTextFormat(
				L"Segoe UI",                // Font family name.
				nullptr,                       // Font collection (NULL sets it to use the system font collection).
				DWRITE_FONT_WEIGHT_REGULAR,
				DWRITE_FONT_STYLE_NORMAL,
				DWRITE_FONT_STRETCH_NORMAL,
				72.0f,
				L"",
				&text_format);
			text_format->SetTextAlignment(DWRITE_TEXT_ALIGNMENT::DWRITE_TEXT_ALIGNMENT_CENTER);
			text_format->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
		}
		~text()
		{
			if (text_format)
				text_format->Release();
		}
	};
}