// Copyright (c) Orange Lee. Licensed under the MIT Licence.
// See the LICENCE file in the repository root for full licence text.

#pragma once

#include "pch.h"

#include "widget.h"

namespace D2DDemo::HiraganaAndKatakana::UI::Widget
{
	class canvas : public widget
	{
	public:
		std::function<void(canvas* obj, int cx, int cy)> size_proc;

	public:
		virtual bool OnHitTest(int x, int y) override { return false; }
		virtual bool OnSize(int cx, int cy) { if (size_proc) size_proc(this, cx, cy); return false; }

	public:
		std::vector<std::unique_ptr<widget>> content;

	public:
		virtual bool wander_pre(wander_func func, const wander_struct& ws = wander_struct{}) override
		{
			bool ret = func(this, ws);
			if (ret) for (const auto& t : content)
			{
				ret &= t->wander_pre(func, wander_struct{ ws.relative_x + left, ws.relative_y + top });
				if (!ret)
					break;
			}
			return ret;
		}
		virtual bool wander_post(wander_func func, const wander_struct& ws = wander_struct{}) override
		{
			bool ret = true;
			for (const auto& t : content)
			{
				ret &= t->wander_post(func, wander_struct{ ws.relative_x + left, ws.relative_y + top });
				if (!ret)
					break;
			}
			if (ret)
				ret &= func(this, ws);
			return ret;
		}

	public:
		canvas() = default;
		canvas(std::initializer_list<widget*> list)
		{
			for (auto* t : list)
			{
				content.push_back(std::move(std::unique_ptr<widget>(t)));
			}
		}
	};
}