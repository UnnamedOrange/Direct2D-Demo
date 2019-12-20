// Copyright (c) Orange Lee. Licensed under the MIT Licence.
// See the LICENCE file in the repository root for full licence text.

#pragma once

#include "pch.h"

namespace D2DDemo::RandomGraphics::Window
{
	class MainWindow : public TWindowNormal,
		public TWinAug::TDPI,
		public TWinAug::TWinSize
	{
		virtual LRESULT WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) override;

	private:
		ID2D1HwndRenderTarget* pRenderTarget{};
		void CreateD2DRenderTarget();
		void ReleaseD2DRenderTarget();

	private:
		struct RandomElement
		{
			enum class Element
			{
				Ellipse,
				Rectangle
			};
			Element ele;
			D2D1_POINT_2L lt, rb;
			ID2D1LinearGradientBrush* brush{};

			void RandomBrush(ID2D1HwndRenderTarget* pRenderTarget)
			{
				int maxx = GetSystemMetrics(SM_CXSCREEN);
				int maxy = GetSystemMetrics(SM_CYSCREEN);
				static std::default_random_engine engine;
				std::uniform_real_distribution dis(0.0, 1.0);
				D2D1_GRADIENT_STOP stops[2]{
					D2D1::GradientStop(0, D2D1::ColorF(dis(engine), dis(engine), dis(engine), dis(engine))),
					D2D1::GradientStop(1, D2D1::ColorF(dis(engine), dis(engine), dis(engine), dis(engine)))
				};

				ID2D1GradientStopCollection* collection{};
				if (!SUCCEEDED(pRenderTarget->CreateGradientStopCollection(stops, std::size(stops), &collection)))
					throw std::runtime_error("Fail to CreateGradientStopCollection.");
				if (!SUCCEEDED(pRenderTarget->CreateLinearGradientBrush(D2D1::LinearGradientBrushProperties(D2D1::Point2F(0, 0), D2D1::Point2F(maxx, maxy)),
					collection, &brush)))
					throw std::runtime_error("Fail to CreateLinearGradientBrush.");
				if (collection) // ID2D1GradientStopCollection 创建完 brush 就可以销毁了
				{
					collection->Release();
					collection = nullptr;
				}
			}
			RandomElement(ID2D1HwndRenderTarget* pRenderTarget)
			{
				static std::default_random_engine engine;
				std::uniform_int_distribution dis(0, 1);
				ele = static_cast<Element>(dis(engine));
				int maxx = GetSystemMetrics(SM_CXSCREEN);
				int maxy = GetSystemMetrics(SM_CYSCREEN);
				new(&dis) std::uniform_int_distribution(0, maxx);
				lt = D2D1::Point2(dis(engine), 0);
				rb = D2D1::Point2(dis(engine), 0);
				new(&dis) std::uniform_int_distribution(0, maxy);
				lt.y = dis(engine);
				rb.y = dis(engine);

				RandomBrush(pRenderTarget);
			}
			RandomElement(RandomElement&& another) noexcept
			{
				ele = another.ele;
				lt = another.lt;
				rb = another.rb;
				brush = another.brush; // 必须编写移动构造函数，否则在 push_back 时将调用析构函数
				another.brush = nullptr;
			}
			~RandomElement()
			{
				if (brush)
				{
					brush->Release();
					brush = nullptr;
				}
			}
		};
		std::vector<RandomElement> elements;
		void GenerateElements();
		void Paint();

	public:
		MainWindow();
	};
}