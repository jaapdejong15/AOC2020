#include "day13.h"
#include <algorithm>

int day13_1(Timer& timer)
{
	std::vector<std::string> input = getStringInput("input13.txt");
	timer.start();
	int startTime = std::stoi(input[0]);
	std::vector<std::string> busesStr = splitter(input[1], ',');
	std::vector<int> busNumbers;
	for (std::string bus : busesStr) {
		if (bus[0] != 'x') {
			busNumbers.push_back(std::stoi(bus));
		}
	}
	int minTime = INT32_MAX;
	int busnr = 0;
	for (int nr : busNumbers) {
		if ((nr - (startTime % nr)) < minTime) {
			busnr = nr;
			minTime = (nr - (startTime % nr));
		}
	}
	timer.stop();
	return minTime * busnr;
}

unsigned long long day13_2(Timer& timer)
{
	std::vector<std::string> input = getStringInput("input13.txt");
	timer.start();
	std::vector<std::string> busesStr = splitter(input[1], ',');
	unsigned long long inc = std::stoi(busesStr[0]);
	unsigned long long t = std::stoi(busesStr[0]);

	for (int i = 1; i < busesStr.size(); i++) {
		if (busesStr[i][0] != 'x') {
			while ((t + i) % std::stoi(busesStr[i]) != 0) {
				t += inc;
			}
			inc *= std::stoi(busesStr[i]);
		}
		
	}
	timer.stop();
	return t;
}
