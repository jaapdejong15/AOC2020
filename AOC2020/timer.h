#pragma once

#include <fstream>
#include <iostream>
#include <chrono>
#include <vector>
#include <string>

class Timer {
private:
	std::chrono::steady_clock::time_point start_time;
	std::chrono::steady_clock::time_point stop_time;
	std::vector<double> times;
public:
	Timer();
	void start();
	void stop();
	std::tuple<double, int> getTimingData();
};
