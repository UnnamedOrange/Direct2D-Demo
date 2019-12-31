// Copyright (c) Orange Lee. Licensed under the MIT Licence.
// See the LICENCE file in the repository root for full licence text.

#pragma once

#include "pch.h"

namespace D2DDemo::HiraganaAndKatakana::UI::Widget
{
	struct draw_struct
	{
		ID2D1RenderTarget* render_target;
		int relative_x;
		int relative_y;
	};
}