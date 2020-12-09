#include "day9.h"
#include "helper.h"
#include <algorithm>
#include <algorithm>
#include "timer.h"

int day9_1(std::string filename, Timer &timer) {
	std::vector<uint64_t> input = getInt64Input("input9.txt");

	timer.start();

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

	timer.stop();
	return answer;
}

int day9_2(std::string filename, Timer &timer) {
	std::vector<std::uint_fast64_t> input = getInt64Input("input9.txt");
	uint64_t part1_answer = 257342611;

	timer.start();

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
	timer.stop();
	return max + min;
}
