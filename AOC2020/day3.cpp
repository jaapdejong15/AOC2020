#include "day3.h"
#include <tuple>

std::vector<std::vector<bool>> getInput() {
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

std::vector<std::vector<bool>> input = getInput();

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

void day3_1() {
	auto start = std::chrono::high_resolution_clock::now();
	
	long long answer = count(3, 1);

	auto stop = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double, std::milli> time = stop - start;
	printf("==========\nPART 1\nAnswer:        %lld\nCalculated in: %f ms\n==========", answer, time.count());
}

void day3_2() {
	auto start = std::chrono::high_resolution_clock::now();

	long long answer = count(1, 1) * count(3, 1) * count(5, 1) * count(7, 1) * count(1, 2);

	auto stop = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double, std::milli> time = stop - start;
	printf("==========\nPART 2\nAnswer:        %lld\nCalculated in: %f ms\n==========", answer, time.count());

}
