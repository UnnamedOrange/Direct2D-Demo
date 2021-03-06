﻿// Copyright (c) Orange Lee. Licensed under the MIT Licence.
// See the LICENCE file in the repository root for full licence text.

#include "pch.h"

#include "Main Window.h"

#include "main.h"

using namespace D2DDemo::ProcessRing::Layout;

LRESULT D2DDemo::ProcessRing::Window::MainWindow::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hwnd, WM_CREATE, [this](HWND hwnd, LPCREATESTRUCT lpCreateStruct)->BOOL
			{
				CreateD2DRenderTarget();

				set_properties();
				for (int i = 0; i < std::size(circles); i++)
				{
					circles[i].reset_start_time(i * circles[i].T / (std::size(circles) + 8));
				}
				return TRUE;
			});
		HANDLE_MSG(hwnd, WM_DESTROY, [this](HWND hwnd)->void
			{
				PostQuitMessage(0);
			});
		HANDLE_MSG(hwnd, WM_SIZE, [this](HWND hwnd, UINT state, int cx, int cy)->void
			{
				pRenderTarget->Resize(D2D1::SizeU(cx, cy));
				set_properties();
			});
		HANDLE_MSG(hwnd, WM_SETFOCUS, [this](HWND hwnd, HWND hwndOldFocus)->void
			{
				is_focus = true;
			});
		HANDLE_MSG(hwnd, WM_KILLFOCUS, [this](HWND hwnd, HWND hwndNewFocus)->void
			{
				is_focus = false;
			});

		HANDLE_MSG(hwnd, WM_PAINT, OnPaint);

	default:
		return DefWindowProcW(hwnd, message, wParam, lParam);
	}
	return 0;
}
void D2DDemo::ProcessRing::Window::MainWindow::OnPaint(HWND hwnd)
{
	using clock = std::chrono::high_resolution_clock;
	dq.push_back(clock::now().time_since_epoch().count());
	if (dq.size() > 15)
		dq.pop_front();
	std::wstring str_fps;
	if (dq.size() > 1)
	{
		int fps = (long double)(dq.size() - 1) * clock::period::den / (dq.back() - dq.front()) + 0.5;
		str_fps = std::to_wstring(fps);
	}
	if (!is_focus)
		std::this_thread::sleep_for(std::chrono::duration<long long, std::ratio<1, 16>>(1));

	pRenderTarget->BeginDraw();
	Paint();
	pRenderTarget->EndDraw();

	HDC hdc = GetDC(GetHwnd());
	TextOutW(hdc, 0, 0, str_fps.c_str(), str_fps.length());
	ReleaseDC(GetHwnd(), hdc);

	ValidateRect(hwnd, NULL); // note
}

void D2DDemo::ProcessRing::Window::MainWindow::CreateD2DRenderTarget()
{
	if (FAILED(Main::App().pFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_DEFAULT, D2D1::PixelFormat(), USER_DEFAULT_SCREEN_DPI, USER_DEFAULT_SCREEN_DPI),
		D2D1::HwndRenderTargetProperties(GetHwnd()),
		&pRenderTarget)))
		throw std::runtime_error("Fail to CreateHwndRenderTarget.");
}
void D2DDemo::ProcessRing::Window::MainWindow::ReleaseD2DRenderTarget()
{
	if (pRenderTarget)
	{
		pRenderTarget->Release();
		pRenderTarget = nullptr;
	}
}

void D2DDemo::ProcessRing::Window::MainWindow::set_properties()
{
	for (auto& c : circles)
	{
		c.set_property(CircleObject::Property{
			D2D1::Point2F(static_cast<FLOAT>(width) / 2, static_cast<FLOAT>(height) / 2),
			static_cast<FLOAT>(50.0f * dpi) });
	}
}

void D2DDemo::ProcessRing::Window::MainWindow::Paint()
{
	pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));

	for (auto& c : circles)
	{
		c.update();
		c.draw(pRenderTarget);
	}
}

D2DDemo::ProcessRing::Window::MainWindow::MainWindow()
{
	property__lpWindowName__(L"Process Ring");
}

int D2DDemo::ProcessRing::Window::MainWindow::PeekMessageLoop()
{
	MSG msg;
	while (true)
	{
		if (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}
		else
			OnPaint(GetHwnd());
	}
	return msg.wParam;
}