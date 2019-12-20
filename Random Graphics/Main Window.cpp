// Copyright (c) Orange Lee. Licensed under the MIT Licence.
// See the LICENCE file in the repository root for full licence text.

#include "pch.h"

#include "Main Window.h"

#include "main.h"

LRESULT D2DDemo::RandomGraphics::Window::MainWindow::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hwnd, WM_CREATE, [this](HWND hwnd, LPCREATESTRUCT lpCreateStruct)->BOOL
			{
				CreateD2DRenderTarget();
				GenerateElements(); // 在 CreateD2DRenderTarget 之后再生成。
				return TRUE;
			});
		HANDLE_MSG(hwnd, WM_DESTROY, [this](HWND hwnd)->void
			{
				PostQuitMessage(0);
			});
		HANDLE_MSG(hwnd, WM_SIZE, [this](HWND hwnd, UINT state, int cx, int cy)->void
			{
				pRenderTarget->Resize(D2D1::SizeU(cx, cy));
			});

		HANDLE_MSG(hwnd, WM_PAINT, [this](HWND hwnd)->void
			{
				pRenderTarget->BeginDraw();
				Paint();
				pRenderTarget->EndDraw();
				ValidateRect(hwnd, NULL); // note
			});

	default:
		return DefWindowProcW(hwnd, message, wParam, lParam);
	}
	return 0;
}

void D2DDemo::RandomGraphics::Window::MainWindow::CreateD2DRenderTarget()
{
	if (FAILED(Main::App().pFactory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(GetHwnd(), D2D1::SizeU(1920, 1080)),
		&pRenderTarget)))
		throw std::runtime_error("Fail to CreateHwndRenderTarget.");
	pRenderTarget->SetDpi(USER_DEFAULT_SCREEN_DPI, USER_DEFAULT_SCREEN_DPI);
}
void D2DDemo::RandomGraphics::Window::MainWindow::ReleaseD2DRenderTarget()
{
	if (pRenderTarget)
	{
		pRenderTarget->Release();
		pRenderTarget = nullptr;
	}
}

D2DDemo::RandomGraphics::Window::MainWindow::MainWindow()
{
	property__lpWindowName__(L"Random Graphics");
}

void D2DDemo::RandomGraphics::Window::MainWindow::GenerateElements()
{
	elements.clear();
	for (int i = 0; i < 100; i++)
		elements.push_back(RandomElement(pRenderTarget));
}
void D2DDemo::RandomGraphics::Window::MainWindow::Paint()
{
	pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
	for (const auto& t : elements)
	{
		auto center = D2D1::Point2F(t.lt.x + t.rb.x >> 1, t.lt.y + t.rb.y >> 1);
		int cx = t.rb.x - t.lt.x;
		int cy = t.rb.y - t.lt.y;
		switch (t.ele)
		{
		case RandomElement::Element::Ellipse:
		{
			pRenderTarget->FillEllipse(D2D1::Ellipse(center, cx / 2, cy / 2), t.brush);
			break;
		}
		case RandomElement::Element::Rectangle:
		{
			pRenderTarget->FillRectangle(D2D1::RectF(t.lt.x, t.lt.y, t.rb.x, t.rb.y), t.brush);
			break;
		}
		default:
			break;
		}
	}
}