// Copyright (c) Orange Lee. Licensed under the MIT Licence.
// See the LICENCE file in the repository root for full licence text.

#pragma once

#include "pch.h"

#include "draw.h"
#include "widget.h"

namespace D2DDemo::HiraganaAndKatakana::UI::Widget
{
	class root
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

	private:
		std::unique_ptr<widget> __content;

	public:
		widget* content() const { return __content.get(); }
		[[nodiscard]] widget* content(widget* new_one) { auto* ret = __content.release(); __content.reset(new_one); return ret; }

	public:
		bool resize(std::optional<int> cx, std::optional<int> cy)
		{
			if (cx.has_value())
				__width = cx.value();
			if (cy.has_value())
				__height = cy.value();

			if (content())
				return content()->resize(cx, cy);
			return false;
		}
		bool update()
		{
			bool ret = false;
			if (content())
			{
				content()->wander_pre([&](widget* obj, const widget::wander_struct& ws)->bool
					{
						ret |= obj->OnUpdate();
						return true;
					});
			}
			return ret;
		}
		void draw(void* obj)
		{
			auto* render_target = reinterpret_cast<ID2D1RenderTarget*>(obj);
			if (content())
			{
				content()->wander_pre([&](widget* obj, const widget::wander_struct& ws)->bool
					{
						obj->OnDraw(draw_struct{ render_target, ws.relative_x, ws.relative_y });
						return true;
					});
			}
		}
		bool click(int x, int y)
		{
			bool ret = false;
			if (content())
			{
				content()->wander_post([&](widget* obj, const widget::wander_struct& ws)->bool
					{
						if (obj->OnHitTest(x - ws.relative_x, y - ws.relative_y))
						{
							ret |= obj->OnClick(x - ws.relative_x, y - ws.relative_y);
							return false;
						}
						return true;
					});
			}
			return ret;
		}
	};
}