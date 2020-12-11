#include "day11.h"

std::vector<std::vector<int>> getInput(std::string filename) {
	std::ifstream file(filename);
	std::vector<std::vector<int>> input;
	for (std::string line; std::getline(file, line);) {
		std::vector<int> row;
		for (char c : line) {
			switch (c) {
			case 'L':
				row.push_back(1);
				break;
			case '.':
				row.push_back(0);
				break;
			default:
				break;
			}
		}
		input.push_back(row);
	}
	return input;
}

int day11_1(Timer& timer)
{
	timer.start();
	std::vector<std::vector<int>> previous = getInput("input11.txt");
	bool change = true;
	while (change) {
		change = false;
		std::vector<std::vector<int>> next;
		for (int y = 0; y < previous.size(); y++) {
			std::vector<int> row;
			for (int x = 0; x < previous[0].size(); x++) {
				if (previous[y][x] > 0) {
					int numOccupied = 0;
					numOccupied = (x - 1 >= 0 && y - 1 >= 0 && previous[y - 1][x - 1] == 2)
						+ (x - 1 >= 0 && previous[y][x - 1] == 2)
						+ (x - 1 >= 0 && y + 1 < previous.size() && previous[y + 1][x - 1] == 2)
						+ (y - 1 >= 0 && previous[y - 1][x] == 2)
						+ (y + 1 < previous.size() && previous[y + 1][x] == 2)
						+ (x + 1 < previous[0].size() && y - 1 >= 0 && previous[y - 1][x + 1] == 2)
						+ (x + 1 < previous[0].size() && previous[y][x + 1] == 2)
						+ (x + 1 < previous[0].size() && y + 1 < previous.size() && previous[y + 1][x + 1] == 2);
					if (previous[y][x] == 1 && numOccupied == 0) {
						change = true;
						row.push_back(2);
					}
					else if (previous[y][x] == 2 && numOccupied >= 4) {
						change = true;
						row.push_back(1);
					}
					else {
						row.push_back(previous[y][x]);
					}
				}
				else {
					row.push_back(0);
				}
			}
			next.push_back(row);
		}
		previous = next;
	}

	int numOccupied = 0;
	for (std::vector<int> row : previous) {
		for (int x : row) {
			numOccupied += (x == 2);
		}
	}
	timer.stop();
	return numOccupied;
}

bool checkDirection(int pos_x, int pos_y, int dir_x, int dir_y, std::vector<std::vector<int>> &input) {
	pos_x += dir_x;
	pos_y += dir_y;
	while (pos_x >= 0 && pos_y >= 0 && pos_x < input[0].size() && pos_y < input.size()) {
		if (input[pos_y][pos_x] == 2) {
			return true;
		}
		else if (input[pos_y][pos_x] == 1) {
			return false;
		}
		pos_x += dir_x;
		pos_y += dir_y;
	}
	return false;
}

int day11_2(Timer& timer)
{
	std::vector<std::vector<int>> previous = getInput("input11.txt");
	timer.start();
	bool change = true;
	while (change) {
		change = false;
		std::vector<std::vector<int>> next;
		for (int y = 0; y < previous.size(); y++) {
			std::vector<int> row;
			for (int x = 0; x < previous[0].size(); x++) {
				if (previous[y][x] > 0) {
					int numOccupied = 0;
					numOccupied += checkDirection(x, y, -1, -1, previous)
						+ checkDirection(x, y, -1, 0, previous)
						+ checkDirection(x, y, -1, 1, previous)
						+ checkDirection(x, y, 0, -1, previous)
						+ checkDirection(x, y, 0, 1, previous)
						+ checkDirection(x, y, 1, -1, previous)
						+ checkDirection(x, y, 1, 0, previous)
						+ checkDirection(x, y, 1, 1, previous);
					if (previous[y][x] == 1 && numOccupied == 0) {
						change = true;
						row.push_back(2);
					} else if (previous[y][x] == 2 && numOccupied >= 5) {
						change = true;
						row.push_back(1);
					} else {
						row.push_back(previous[y][x]);
					}
				} else {
					row.push_back(0);
				}
			}
			next.push_back(row);
		}
		previous = next;
	}
	int numOccupied = 0;
	for (std::vector<int> row : previous) {
		for (int x : row) {
			numOccupied += (x == 2);
		}
	}
	timer.stop();
	return numOccupied;
}
