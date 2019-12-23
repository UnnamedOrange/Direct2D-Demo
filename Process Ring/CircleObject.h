// Copyright (c) Orange Lee. Licensed under the MIT Licence.
// See the LICENCE file in the repository root for full licence text.

#pragma once

#include "pch.h"

namespace D2DDemo::ProcessRing::Layout
{
	class CircleObject
	{
	public:
		struct Property
		{
			D2D1_POINT_2F center{};
			FLOAT radius{};
			FLOAT get_circle_size() const
			{
				return radius * 0.2f;
			}
		};
	private:
		using clock = std::chrono::high_resolution_clock;
		clock::duration t{};
		clock::time_point start_time{ clock::now() };
	public:
		void reset_start_time(clock::duration delta = clock::duration(0))
		{
			start_time = clock::now() + delta;
		}
	private:
		void next_timeline()
		{
			auto now = clock::now();
			t += now - start_time;
			start_time = now;
			update_layout();
		}
		void update_layout()
		{
			// 啥也不干
		}

	public:
		static constexpr clock::duration T{ std::chrono::duration_cast<clock::duration>(std::chrono::milliseconds(1500)) };
		void update()
		{
			next_timeline();
		}

	public:
		void draw(ID2D1RenderTarget* render_target) const
		{
			auto crt_t = t;
			crt_t = (crt_t % T + T) % T;

			constexpr FLOAT pi{ 3.14159265358979323846264f };
			FLOAT x = 2 * pi * crt_t.count() / T.count();
			FLOAT s, c;
			D2D1SinCos(x, &s, &c);
			FLOAT move = -s + x;
			move = pi / 2 - move;
			D2D1SinCos(move, &s, &c);

			D2D1_POINT_2F center{ prop.center.x + prop.radius * c, prop.center.y - prop.radius * s };

			ID2D1SolidColorBrush* brush{};
			render_target->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Orange), &brush);
			render_target->FillEllipse(D2D1::Ellipse(center, prop.get_circle_size() / 2, prop.get_circle_size() / 2), brush);
			brush->Release();
		}

	private:
		Property prop;
	public:
		void set_property(Property property) { prop = property; }
	};
}