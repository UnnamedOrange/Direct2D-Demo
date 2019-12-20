// Copyright (c) Orange Lee. Licensed under the MIT Licence.
// See the LICENCE file in the repository root for full licence text.

#include "pch.h"

#include "main.h"

#include "Main Window.h"

using namespace D2DDemo::HelloDirect2D;
using namespace D2DDemo::HelloDirect2D::Window;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE, _In_ LPWSTR, _In_ int)
{
	return Main::Execute(hInstance);
}

int D2DDemo::HelloDirect2D::Main::OnExecute()
{
	CreateD2DFactory();

	auto window{ std::make_unique<MainWindow>() };
	window->Create(hInstance, nullptr);
	ShowWindow(window->GetHwnd(), SW_SHOW);
	UpdateWindow(window->GetHwnd());
	return window->MessageLoop();
}

void D2DDemo::HelloDirect2D::Main::CreateD2DFactory()
{
	if (FAILED(D2D1CreateFactory(
		D2D1_FACTORY_TYPE::D2D1_FACTORY_TYPE_MULTI_THREADED, &pFactory)))
		throw std::runtime_error("Fail to D2D1CreateFactory.");
}
D2DDemo::HelloDirect2D::Main::~Main()
{
	if (pFactory) pFactory->Release();
}