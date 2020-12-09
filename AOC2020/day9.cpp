#include "day9.h"
#include <algorithm>

std::vector<uint64_t> getInt64Input(std::string input_file) {
	std::ifstream file("input9.txt");
	std::vector<uint64_t> lines;
	for (std::string line; std::getline(file, line);) {
		lines.push_back(std::stoll(line));
	}
	return lines;
}

void day9_1(std::string input_file) {
	std::vector<uint64_t> input = getInt64Input("input9.txt");

	auto start = std::chrono::high_resolution_clock::now();

	std::vector<uint64_t> last25;
	for (int i = 0; i < 25; i++) {
		last25.push_back(input[i]);
	}
	uint64_t answer = 0;

	for (uint16_t x = 25; x < input.size(); x++) {
		bool found = false;
		loop1: for (uint16_t i = 0; i < 25; i++) {
			for (uint16_t j = i + 1; j < 25; j++) {
				if (last25[i] + last25[j] == input[x]) {
					found = true;
					goto found;
				}
			}
 		}
		answer = input[x];
		break;
	found:
		last25.erase(last25.begin());
		last25.push_back(input[x]);
	}

	auto stop = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> time = stop - start;
	printf("==========\nPART 1\nAnswer:        %dll\nCalculated in: %f ms\n==========\n", answer, time.count());
}

void day9_2(std::string input_file) {
	std::vector<std::uint_fast64_t> input = getInt64Input("input9.txt");
	uint64_t part1_answer = 257342611;

	auto start = std::chrono::high_resolution_clock::now();

	std::uint_fast64_t max = 0;
	std::uint_fast64_t min = part1_answer;
	for (uint16_t i = 0; i < input.size(); i++) {
		std::uint_fast64_t sum = 0;
		uint16_t j = i;
		while (sum < part1_answer) {
			sum += input[j];
			j++;
		}
		if (sum == part1_answer) {
			for (std::uint_fast16_t k = i; k < j - 1; k++) {
				max = std::max(max, input[k]);
				min = std::min(min, input[k]);
			}
		}
	}
	auto stop = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> time = stop - start;
	printf("==========\nPART 2\nAnswer:        %dll\nCalculated in: %f ms\n==========\n", max + min, time.count());
	
}
