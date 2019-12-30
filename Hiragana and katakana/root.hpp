// Copyright (c) Orange Lee. Licensed under the MIT Licence.
// See the LICENCE file in the repository root for full licence text.

#pragma once

#include "pch.h"

#include "widget.hpp"

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
		std::unique_ptr<widget> content;

	public:
		void Resize(std::optional<int> cx, std::optional<int> cy)
		{
			if (cx.has_value())
				__width = cx.value();
			if (cy.has_value())
				__height = cy.value();

			if (content)
				content->Resize(cx, cy);
		}
		void OnClick(int x, int y)
		{
			if (content)
			{
				content->wander_post([&](widget* obj)->bool
					{

					});
			}
		}
	};
}