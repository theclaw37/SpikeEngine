#pragma once

#include <chrono>

namespace SpikeUtils
{
	class __declspec(dllexport) Timer
	{
	public:
		enum Milliseconds;
		enum Seconds;
		enum FramesPerSecond;

		template<typename T>
		const double Measure();

		template<> const double Measure<Milliseconds>();
		template<> const double Measure<Seconds>();
		template<> const double Measure<FramesPerSecond>();
		
		const Timer& Start();
	private:
		std::chrono::time_point<std::chrono::steady_clock> _start;
	};
}