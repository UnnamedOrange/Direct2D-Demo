// Copyright (c) Orange Lee. Licensed under the MIT Licence.
// See the LICENCE file in the repository root for full licence text.

#include "pch.h"

#include "Main Window.h"

#include "main.h"

LRESULT D2DDemo::HelloDirect2D::Window::MainWindow::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hwnd, WM_DESTROY, [this](HWND hwnd)->void
			{
				PostQuitMessage(0);
			});

	default:
		return DefWindowProcW(hwnd, message, wParam, lParam);
	}
	return 0;
}