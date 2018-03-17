#pragma once

#include <chrono>

namespace SpikeUtils
{
	class __declspec(dllexport) Timer
	{
	public:
		const long long HowLong();
		const Timer& Start();
	private:
		std::chrono::time_point<std::chrono::steady_clock> _start;
	};
}