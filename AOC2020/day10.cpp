#include "day10.h"
#include <algorithm>

int day10_1(Timer &timer) {
	std::vector<int_fast16_t> input = getIntInput("input10.txt");

	timer.start();
	std::sort(input.begin(), input.end());

	input.insert(input.begin(), 0);
	int num1 = 0;
	int num3 = 1; // built-in adapter
	std::int_fast16_t difference;
	for (size_t i = 0; i < input.size(); i++) {
		difference = input[i] - input[i - 1];
		num1 += difference == 1;
		num3 += difference == 3;
	}

	timer.stop();
	return num1 * num3;
}

std::vector<int> input;
std::vector<std::int_fast64_t> m;

std::int_fast64_t validWaysToReach(int x) {
	int joltage = input[x];
	std::int_fast64_t result = 0;

	for (int i = std::max(x - 3, 0); i < x; i++) {
		if (joltage - input[i] <= 3) {
			if (m[i] == 0) m[i] = validWaysToReach(i);
			result += m[i];
		}
	}
	return result;
}


std::int_fast64_t day10_2(Timer &timer) {
	input = getIntInput("input10.txt");
	m.clear();
	timer.start();
	std::sort(input.begin(), input.end());
	input.insert(input.begin(), 0);
	input.push_back(input[input.size() - 1] + 3);

	m.push_back(1);
	for (int i = 1; i < input.size(); i++) {
		m.push_back(0);
	}
	std::int_fast64_t answer = validWaysToReach(input.size() - 1);
	timer.stop();
	return answer;
}
