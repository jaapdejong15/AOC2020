#include "day5.h"

#include <algorithm>

void day5_1() {
	std::ifstream file("input5.txt");
	std::vector<std::string> lines;
	for (std::string line; std::getline(file, line);) {
		lines.push_back(line);
	}

	int max_seat_id = 0;
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
		max_seat_id = std::max(max_seat_id, row * 8 + column);
	}
	printf("Max seat id: %d\n", max_seat_id);
}