// Copyright (c) Orange Lee. Licensed under the MIT Licence.
// See the LICENCE file in the repository root for full licence text.

#pragma once

#include "pch.h"

namespace D2DDemo::Utils
{
	class PerforamnceCounter
	{
		INT64 frequency; // per second，可缓存

	public:
		PerforamnceCounter()
		{
			QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&frequency));
		}
		static constexpr INT64 rate = 10'000'000;
		INT64 operator()() const // 单位 100 ns
		{
			INT64 ret;
			QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&ret));
			return ret * rate / frequency;
		}
	};
}