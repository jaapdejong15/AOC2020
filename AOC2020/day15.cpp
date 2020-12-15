#include "day15.h"
#include <unordered_map>
#include <map>

long long day15_1(Timer& timer)
{
	std::vector<unsigned long long> starting_numbers = { 9,12,1,4,17,0,18 };
	std::unordered_map<unsigned long long, unsigned long long> memory;

	timer.start();
	int t = 0;
	for (; t < starting_numbers.size() - 1; t++) {
		memory[starting_numbers[t]] = t;
	}

	unsigned long long lastNumberSpoken = starting_numbers[starting_numbers.size() - 1];
	unsigned long long currentNumber = 0;
	for (; t < 2020 - 1; t++) {
		if (memory.find(lastNumberSpoken) != memory.end()) {
			currentNumber = t - memory[lastNumberSpoken];
		}
		else {
			currentNumber = 0;
		}
		memory[lastNumberSpoken] = t;
		lastNumberSpoken = currentNumber;
	}
	timer.stop();
	return lastNumberSpoken;
}

long long day15_2(Timer& timer)
{
	std::vector<unsigned long long> starting_numbers = { 9,12,1,4,17,0,18 };
	std::unordered_map<unsigned long long, unsigned long long> memory;
	memory.reserve(10000);

	timer.start();
	int t = 0;
	for (; t < starting_numbers.size() - 1; t++) {
		memory[starting_numbers[t]] = t;
	}

	unsigned long long lastNumberSpoken = starting_numbers[starting_numbers.size() - 1];
	unsigned long long currentNumber = 0;
	for (; t < 30000000 - 1; t++) {
		if (memory.find(lastNumberSpoken) != memory.end()) {
			currentNumber = t - memory[lastNumberSpoken];
		}
		else {
			currentNumber = 0;
		}
		memory[lastNumberSpoken] = t;
		lastNumberSpoken = currentNumber;
	}
	timer.stop();
	return lastNumberSpoken;
}
