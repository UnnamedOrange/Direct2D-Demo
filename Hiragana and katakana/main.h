// Copyright (c) Orange Lee. Licensed under the MIT Licence.
// See the LICENCE file in the repository root for full licence text.

#pragma once

#include "pch.h"

namespace D2DDemo::HiraganaAndKatakana
{
	class Main : public TApplication<Main>
	{
	public:
		using TApplication<Main>::TApplication;
		virtual int OnExecute() override;

	public:
		ID2D1Factory* pFactory{};
		void CreateD2DFactory();
		~Main();
	};
}