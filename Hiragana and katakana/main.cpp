﻿// Copyright (c) Orange Lee. Licensed under the MIT Licence.
// See the LICENCE file in the repository root for full licence text.

#include "pch.h"

#include "main.h"

#include "Main Window.h"

using namespace D2DDemo::HiraganaAndKatakana;
using namespace D2DDemo::HiraganaAndKatakana::Window;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE, _In_ LPWSTR, _In_ int)
{
	return Main::Execute(hInstance);
}

int D2DDemo::HiraganaAndKatakana::Main::OnExecute()
{
	CreateD2DFactory();

	auto window{ std::make_unique<MainWindow>() };
	window->Create(hInstance, nullptr);
	ShowWindow(window->GetHwnd(), SW_SHOW);
	UpdateWindow(window->GetHwnd());
	return window->MessageLoop();
}

void D2DDemo::HiraganaAndKatakana::Main::CreateD2DFactory()
{
	if (FAILED(D2D1CreateFactory(
		D2D1_FACTORY_TYPE::D2D1_FACTORY_TYPE_MULTI_THREADED, &pFactory)))
		throw std::runtime_error("Fail to D2D1CreateFactory.");

	if (FAILED(DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(IDWriteFactory),
		reinterpret_cast<IUnknown**>(&pDFactory))))
		throw std::runtime_error("Fail to DWriteCreateFactory.");
}
D2DDemo::HiraganaAndKatakana::Main::~Main()
{
	if (pFactory) pFactory->Release();
	if (pDFactory) pDFactory->Release();
}