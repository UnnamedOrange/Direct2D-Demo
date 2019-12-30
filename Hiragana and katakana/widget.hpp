// Copyright (c) Orange Lee. Licensed under the MIT Licence.
// See the LICENCE file in the repository root for full licence text.

#pragma once

#include "pch.h"

namespace D2DDemo::HiraganaAndKatakana::UI::Widget
{
	class widget
	{
	private:
		int __left;
		int __top;
		int __width;
		int __height;
	public:
		const int& left{ __left };
		const int& top{ __top };
		const int& width{ __width };
		const int& height{ __height };

	public:
		virtual bool OnHitTest(int x, int y)
		{
			return left <= x && x < left + width && top <= y && y < top + height;
		}
		virtual void OnSize(int cx, int cy) {}
		virtual void OnClick() {}

	public:
		virtual void OnDraw(void* object);

	public:
		virtual bool wander_post(std::function<bool(widget * obj)> func) { return func(this); }

	public:
		void Resize(std::optional<int> cx, std::optional<int> cy)
		{
			if (cx.has_value())
				__width = cx.value();
			if (cy.has_value())
				__height = cy.value();

			OnSize(width, height);
		}
	};
}