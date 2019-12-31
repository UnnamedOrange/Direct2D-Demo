// Copyright (c) Orange Lee. Licensed under the MIT Licence.
// See the LICENCE file in the repository root for full licence text.

#pragma once

#include "pch.h"

#include "draw.h"

namespace D2DDemo::HiraganaAndKatakana::UI::Widget
{
	class widget
	{
	private:
		int __left;
		int __top;
		int __width;
		int __height;
		double __scale;
	public:
		const int& left{ __left };
		const int& top{ __top };
		const int& width{ __width };
		const int& height{ __height };
		const double& scale{ __scale };

	public:
		virtual void OnUpdate() {}
		virtual void OnDraw(const draw_struct& ds) {}
		virtual bool OnHitTest(int x, int y) { return left <= x && x < left + width && top <= y && y < top + height; }
		virtual void OnSize(int cx, int cy) {}
		virtual void OnClick(int x, int y) {}

	public:
		struct wander_struct
		{
			int relative_x;
			int relative_y;
		};
		using wander_func = std::function<bool(widget * obj, const wander_struct & ws)>;
		virtual bool wander_pre(wander_func func, const wander_struct& ws = wander_struct{}) { return func(this, ws); }
		virtual bool wander_post(wander_func func, const wander_struct& ws = wander_struct{}) { return func(this, ws); }

	public:
		///<summary>
		/// 设置 widget 的大小。
		///</summary>
		void resize(std::optional<int> cx, std::optional<int> cy)
		{
			if (cx.has_value())
				__width = cx.value();
			if (cy.has_value())
				__height = cy.value();

			OnSize(width, height);
		}
		///<summary>
		/// 设置 widget 的位置。坐标总是相对于其父级 widget。
		///</summary>
		void move(std::optional<int> x, std::optional<int> y)
		{
			if (x.has_value())
				__left = x.value();
			if (y.has_value())
				__top = y.value();
		}
	};
}