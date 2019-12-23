// Copyright (c) Orange Lee. Licensed under the MIT Licence.
// See the LICENCE file in the repository root for full licence text.

#pragma once

#include "pch.h"

#include "DWidget.h"

namespace D2DDemo::HiraganaAndKatakana::Sekai
{
	class Sekai
	{
		int width;
		int height;
		std::unique_ptr<DWidget> widget{};

		// system clock
	public:
		using system_clock = std::chrono::high_resolution_clock;
		///<summary>
		/// 当前时间。
		///</summary>
		std::chrono::nanoseconds crt_time{};
	private:
		///<summary>
		/// 上一次检查的时间点。
		///</summary>
		std::chrono::time_point<system_clock> check_point{ system_clock::now() };
		///<summary>
		/// 时间流逝速率。
		///</summary>
		long double rate{ 1.0L };
	public:
		///<summary>
		/// 重置上一次检查的时间点为当前时间 + delta。
		///</summary>
		void reset_check_point(std::chrono::nanoseconds delta = std::chrono::nanoseconds(0)) { check_point = system_clock::now() + delta; }
		///<summary>
		/// 时间流逝。
		///</summary>
		void go()
		{
			auto now = system_clock::now();
			auto passed = std::chrono::nanoseconds(static_cast<long long>((now - check_point).count() * rate));
			check_point = now;

			// TODO: 告知时间流逝。
		}



	};
}