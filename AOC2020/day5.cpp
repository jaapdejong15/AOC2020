#include "day5.h"
#include <algorithm>


int day5_1(Timer &timer) {
	std::vector<std::string> lines = getStringInput("input5.txt");

	timer.start();

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
	timer.stop();
	return max_seat_id;
}

int day5_2(Timer &timer) {
	std::vector<std::string> lines = getStringInput("input5.txt");

	timer.start();

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
	timer.stop();
	return answer;
}