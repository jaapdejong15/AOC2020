#include "day5.h"

#include <algorithm>

std::vector<std::string> getInput() {
	std::ifstream file("input5.txt");
	std::vector<std::string> lines;
	for (std::string line; std::getline(file, line);) {
		lines.push_back(line);
	}
	return lines;
}

void day5_1() {
	std::vector<std::string> lines = getInput();

	auto start = std::chrono::high_resolution_clock::now();

	int max_seat_id = 0;
	int row;
	int column;
	for (std::string line : lines) {
		row = 0;
		column = 0;
		for (int i = 0; i < line.size(); i++) {
			switch (line[i]) {
			case 'B':
				row += 64 >> i;
				break;
			case 'R':
				column += 4 >> i - 7;
				break;
			default:
				break;
			}
		}
		max_seat_id = std::max(max_seat_id, row * 8 + column);
	}
	auto stop = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double, std::milli> time = stop - start;
	printf("==========\nPART 1\nAnswer:        %d\nCalculated in: %f ms\n==========\n", max_seat_id, time.count());
}

void day5_2() {
	std::vector<std::string> lines = getInput();

	auto start = std::chrono::high_resolution_clock::now();

	std::vector<int> seat_ids;
	for (std::string line : lines) {
		int row = 0;
		int column = 0;
		for (int i = 0; i < line.size(); i++) {
			switch (line[i]) {
			case 'B':
				row += 64 >> i;
				break;
			case 'R':
				column += 4 >> i - 7;
				break;
			default:
				break;
			}
		}
		seat_ids.push_back(row * 8 + column);
	}
	std::sort(seat_ids.begin(), seat_ids.end());
	int last_id = -3;
	int answer = 0;
	for (int id : seat_ids) {
		if (id - last_id == 2) {
			answer = id - 1;
			break;
		}
		last_id = id;
	}
	auto stop = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double, std::milli> time = stop - start;
	printf("==========\nPART 2\nAnswer:        %d\nCalculated in: %f ms\n==========\n", answer, time.count());
}