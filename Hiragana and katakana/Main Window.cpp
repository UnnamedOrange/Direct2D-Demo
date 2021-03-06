﻿// Copyright (c) Orange Lee. Licensed under the MIT Licence.
// See the LICENCE file in the repository root for full licence text.

#include "pch.h"

#include "Main Window.h"

#include "main.h"

#include "rectangle.h"
#include "canvas.h"
#include "text.h"

LRESULT D2DDemo::HiraganaAndKatakana::Window::MainWindow::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
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
				ReleaseD2DRenderTarget();

				PostQuitMessage(0);
			});
		HANDLE_MSG(hwnd, WM_SIZE, [this](HWND hwnd, UINT state, int cx, int cy)->void
			{
				pRenderTarget->Resize(D2D1::SizeU(cx, cy));
				ui.resize(cx, cy);
			});
		HANDLE_MSG(hwnd, WM_LBUTTONDOWN, [this](HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags)->void
			{
				if (ui.click(x, y))
					draw();
			});


		HANDLE_MSG(hwnd, WM_PAINT, OnPaint);

	default:
		return DefWindowProcW(hwnd, message, wParam, lParam);
	}
	return 0;
}
void D2DDemo::HiraganaAndKatakana::Window::MainWindow::OnPaint(HWND hwnd)
{
	pRenderTarget->BeginDraw();
	Paint(pRenderTarget);
	pRenderTarget->EndDraw();

	ValidateRect(hwnd, NULL); // note
}

void D2DDemo::HiraganaAndKatakana::Window::MainWindow::CreateD2DRenderTarget()
{
	if (FAILED(Main::App().pFactory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(GetHwnd(), D2D1::SizeU(width, height)),
		&pRenderTarget)))
		throw std::runtime_error("Fail to CreateHwndRenderTarget.");
	pRenderTarget->SetDpi(USER_DEFAULT_SCREEN_DPI, USER_DEFAULT_SCREEN_DPI);
}
void D2DDemo::HiraganaAndKatakana::Window::MainWindow::ReleaseD2DRenderTarget()
{
	if (pRenderTarget)
	{
		pRenderTarget->Release();
		pRenderTarget = nullptr;
	}
}

void D2DDemo::HiraganaAndKatakana::Window::MainWindow::Paint(ID2D1RenderTarget* render_target)
{
	bool flag = false;
	flag = ui.update();
	ui.draw(render_target);
	if (flag) draw();
}

D2DDemo::HiraganaAndKatakana::Window::MainWindow::MainWindow()
{
	property__lpWindowName__(L"Hiragana and katakana");

	ui.content(new UI::Widget::canvas{
		new UI::Widget::rectangle{0, 0, 0, 0},
		new UI::Widget::rectangle{0, 0, 0, 0},
		new UI::Widget::text{0, 0, 0, 0, L"平仮名と片仮名"},
		});
	dynamic_cast<UI::Widget::canvas*>(ui.content())->size_proc = [&](UI::Widget::canvas* obj, int cx, int cy)
	{
		obj->content[0]->resize(cx / 2, cy);
		obj->content[0]->move(cx / 2, std::nullopt);
		obj->content[1]->resize(cx / 2, cy);
		obj->content[2]->resize(cx, cy);
	};
}

int D2DDemo::HiraganaAndKatakana::Window::MainWindow::PeekMessageLoop()
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