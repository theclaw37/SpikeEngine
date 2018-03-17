#include "Timer.h"

const long long SpikeUtils::Timer::HowLong()
{
	auto elapsed = std::chrono::high_resolution_clock::now() - _start;
	auto elapsedMs = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed);
	
	return elapsedMs.count();
}

const SpikeUtils::Timer & SpikeUtils::Timer::Start()
{
	_start = std::chrono::high_resolution_clock::now();

	return (*this);
}
