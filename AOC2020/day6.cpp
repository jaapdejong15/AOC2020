#include "day6.h"

std::vector<std::string> getInput6() {
	std::ifstream file("input6.txt");
	std::vector<std::string> lines;
	for (std::string line; std::getline(file, line);) {
		lines.push_back(line);
	}
	return lines;
}

void day6_1() {
	std::vector<std::string> input = getInput6();

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
	answers = 0U;
	printf("Answer: %d\n", count);
}

void day6_2() {
	std::vector<std::string> input = getInput6();

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
	printf("Answer: %d\n", count);
}