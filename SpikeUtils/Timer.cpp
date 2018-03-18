#include "Timer.h"

template<>
const double SpikeUtils::Timer::Measure<SpikeUtils::Timer::Milliseconds>()
{
	std::chrono::duration<double, std::milli> elapsed = std::chrono::high_resolution_clock::now() - _start;
	return elapsed.count();
}

template<>
const double SpikeUtils::Timer::Measure<SpikeUtils::Timer::Seconds>()
{
	std::chrono::duration<double> elapsed = std::chrono::high_resolution_clock::now() - _start;
	return elapsed.count();
}

template<>
const double SpikeUtils::Timer::Measure<SpikeUtils::Timer::FramesPerSecond>()
{
	std::chrono::duration<double>  elapsed = std::chrono::high_resolution_clock::now() - _start;
	return 1.0 / elapsed.count();
}

const SpikeUtils::Timer & SpikeUtils::Timer::Start()
{
	_start = std::chrono::high_resolution_clock::now();

	return (*this);
}
