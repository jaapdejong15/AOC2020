#include "day6.h"

int day6_1(Timer &timer) {
	std::vector<std::string> input = getStringInput("input6.txt");

	timer.start();

	int count = 0;
	uint32_t answers = 0;
	for (std::string line : input) {
		if (line.empty()) {
			while (answers > 0) {
				count += answers & 1U;
				answers >>= 1;
			}
			answers = 0U;
		}
		else {
			for (char c : line) {
				answers |= 1U << c - 'a';
			}
		}
	}
	while (answers > 0) {
		count += answers & 1U;
		answers >>= 1;
	}

	timer.stop();
	return count;

}

int day6_2(Timer &timer) {
	std::vector<std::string> input = getStringInput("input6.txt");

	timer.start();

	int count = 0;
	uint32_t answers = 0xFFFFFFFF;
	for (std::string line : input) {
		if (line.empty()) {
			while (answers > 0) {
				count += answers & 1U;
				answers >>= 1;
			}
			answers = 0xFFFFFFFF;
		}
		else {
			uint32_t answer = 0;
			for (char c : line) {
				 answer |= 1U << c - 'a';
			}
			answers &= answer;
		}
	}
	while (answers > 0) {
		count += answers & 1U;
		answers >>= 1;
	}
	answers = 0U;

	timer.stop();
	return count;
}