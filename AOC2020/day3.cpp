#include "day3.h"
#include <tuple>

void day3_1() {
	std::ifstream file("input3.txt");
	std::vector<std::vector<bool>> input;
	for (std::string entry; std::getline(file, entry);) {
		std::vector<bool> line_input;
		for (char c : entry) {
			line_input.push_back(c == '#');
		}
		input.push_back(line_input);
	}
	//printf("input height: %i\ninput width: %i\n", input.size(), input[input.size() - 1].size());

	int input_width = input[0].size();
	int j = 3;
	int answer = 0;
	for (int i = 1; i < input.size(); i++) {
		if (input[i][j % input_width]) {
			answer++;
		}
		j += 3;
	}
	printf("Answer: %i", answer);
}

unsigned long long count(int x, int y, std::vector<std::vector<bool>> input) {
	unsigned long long answer = 0;
	int input_width = input[0].size();
	int j = x;
	for (int i = y; i < input.size(); i += y) {
		if (input[i][j % input_width]) {
			answer++;
		}
		j += x;
	}
	return answer;
}

void day3_2() {
	std::ifstream file("input3.txt");
	std::vector<std::vector<bool>> input;
	for (std::string entry; std::getline(file, entry);) {
		std::vector<bool> line_input;
		for (char c : entry) {
			line_input.push_back(c == '#');
		}
		input.push_back(line_input);
	}
	std::tuple<int, int> directions[5] = {
		std::tuple<int, int>(1, 1),
		std::tuple<int, int>(3, 1),
		std::tuple<int, int>(5, 1),
		std::tuple<int, int>(7, 1),
		std::tuple<int, int>(1, 2)
	};
	unsigned long long answer = count(1, 1, input) * count(3, 1, input) * count(5, 1, input) * count(7, 1, input) * count(1, 2, input);
	printf("Answer: %llu\n", answer);
}
