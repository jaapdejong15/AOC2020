#include "day3.h"
#include <tuple>

std::vector<std::vector<bool>> getInput3() {
	std::ifstream file("input3.txt");
	std::vector<std::vector<bool>> input;
	for (std::string entry; std::getline(file, entry);) {
		std::vector<bool> line_input;
		for (char c : entry) {
			line_input.push_back(c == '#');
		}
		input.push_back(line_input);
	}
	return input;
}

std::vector<std::vector<bool>> input = getInput3();

long long count(int x, int y) {
	unsigned long long answer = 0;
	int input_width = input[0].size();
	int j = x;
	for (int i = y; i < input.size(); i += y) {
		answer += input[i][j % input_width];
		j += x;
	}
	return answer;
}

long long day3_1(Timer &timer) {
	timer.start();
	
	long long answer = count(3, 1);

	timer.stop();
	return answer;
}

long long day3_2(Timer &timer) {
	timer.start();

	long long answer = count(1, 1) * count(3, 1) * count(5, 1) * count(7, 1) * count(1, 2);

	auto stop = std::chrono::high_resolution_clock::now();

	timer.stop();
	return answer;
}
