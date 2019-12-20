// Copyright (c) Orange Lee. Licensed under the MIT Licence.
// See the LICENCE file in the repository root for full licence text.

#include "pch.h"

#include "Main Window.h"

#include "main.h"

LRESULT D2DDemo::HelloDirect2D::Window::MainWindow::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hwnd, WM_CREATE, [this](HWND hwnd, LPCREATESTRUCT lpCreateStruct)->BOOL
			{
				CreateD2DRenderTarget();
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

				pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
				DrawRectangle();

				pRenderTarget->EndDraw();

				ValidateRect(hwnd, NULL); // note
			});

	default:
		return DefWindowProcW(hwnd, message, wParam, lParam);
	}
	return 0;
}

void D2DDemo::HelloDirect2D::Window::MainWindow::CreateD2DRenderTarget()
{
	if (FAILED(Main::App().pFactory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(GetHwnd(), D2D1::SizeU(width, height)),
		&pRenderTarget)))
		throw std::runtime_error("Fail to CreateHwndRenderTarget.");
	pRenderTarget->SetDpi(USER_DEFAULT_SCREEN_DPI, USER_DEFAULT_SCREEN_DPI);
}
void D2DDemo::HelloDirect2D::Window::MainWindow::ReleaseD2DRenderTarget()
{
	if (pRenderTarget)
	{
		pRenderTarget->Release();
		pRenderTarget = nullptr;
	}
}

void D2DDemo::HelloDirect2D::Window::MainWindow::DrawRectangle()
{
	ID2D1SolidColorBrush* brush{};
	pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &brush);
	pRenderTarget->DrawRectangle(D2D1::RectF(20, 20, width - 20, height - 20), brush);
	brush->Release();
}