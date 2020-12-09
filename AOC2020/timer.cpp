#include "timer.h"
#include <tuple>
#include <algorithm>

float getMedian(std::vector<double> input) {
	if (input.size() == 0) {
		return NAN;
	}
	std::sort(input.begin(), input.end());
	if (input.size() % 2 == 0) {
		return (input[input.size() / 2] + input[input.size() / 2 + 1]) / 2;
	}
	return input[input.size() / 2];
}

Timer::Timer() {}

void Timer::start() {
	start_time = std::chrono::high_resolution_clock::now();
}

void Timer::stop() {
	stop_time = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::nano> duration = stop_time - start_time;
	times.push_back(duration.count());
}

// median - sample size (unit = ms)
std::tuple<double, int> Timer::getTimingData() {
	return std::make_tuple(getMedian(times) / 1000000, times.size());
}
