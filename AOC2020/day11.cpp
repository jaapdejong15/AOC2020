#include "day11.h"
#include "grid.h"

std::vector<std::vector<int>> getInput11(std::string filename) {
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
	std::vector<std::vector<int>> previous = getInput11("input11.txt");
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
	std::vector<std::vector<int>> previous = getInput11("input11.txt");
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

int checkAllDirections(Grid::Node* current_node) {
	int count = 0;
	Grid::Node* next_node;
	for (int i = 0; i < 8; i++) {
		next_node = current_node->neighbors[i];

		while (true) {			
			if (next_node == NULL) {
				break;
			} else if (next_node->value == 1) {
				break;
			} else if (next_node->value == 2) {
				count++;
				break;
			} else {
				next_node = next_node->neighbors[i];
			}	
		}
	}
	return count;
}

int checkIf0Directions(Grid::Node* current_node) {
	Grid::Node* next_node;
	for (int i = 0; i < 8; i++) {
		next_node = current_node->neighbors[i];

		while (true) {
			if (next_node == NULL) {
				break;
			}
			else if (next_node->value == 1) {
				break;
			}
			else if (next_node->value == 2) {
				return 1;
				break;
			}
			else {
				next_node = next_node->neighbors[i];
			}
		}
	}
	return 0;
}

void printGrid(Grid::Node* head, int height, int width) {
	Grid::Node* row_start = head;
	Grid::Node* current = head;
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			if (current->value == 0) {
				std::cout << '.';
			}
			else if (current->value == 1) {
				std::cout << 'L';
			}
			else if (current->value == 2) {
				std::cout << '#';
			}
			current = current->neighbors[4];
		}
		std::cout << std::endl;
		row_start = row_start->neighbors[6];
		current = row_start;
	}
	std::cout << std::endl;
}

int day11_2_alternative(Timer& timer) {
	std::vector<std::vector<int>> input = getInput11("input11.txt");
	timer.start();

	Grid g1 = Grid();
	Grid g2 = Grid();
	
	int width = input[0].size();
	int height = input.size();

	bool change = true;
	Grid::Node* head1 = g1.getGrid(input);
	Grid::Node* head2 = g2.getGrid(input); 
	Grid::Node* swap;
	Grid::Node* row_start1 = head1;
	Grid::Node* row_start2 = head2;
	Grid::Node* current1 = head1;
	Grid::Node* current2 = head2;
	int seats;
	while (change) {
		change = false;
		row_start1 = head1;
		row_start2 = head2;
		current1 = head1;
		current2 = head2;
		for (int y = 0; y < height; y++) {
			current1 = row_start1;
			current2 = row_start2;
			for (int x = 0; x < width; x++) {
				if (current1->value == 0) {
					current2->value = current1->value;
				}
				else if (current1->value == 1) {
					seats = checkIf0Directions(current1);
					if (seats == 0) {
						change = true;
						current2->value = 2;
					}
					else {
						current2->value = current1->value;
					}
				}
				else if (current1->value == 2) {
					seats = checkAllDirections(current1);
					if (seats >= 5) {
						change = true;
						current2->value = 1;
					} 
					else {
						current2->value = current1->value;
					}
				}
				
				current1 = current1->neighbors[4];
				current2 = current2->neighbors[4];
			}
			row_start1 = row_start1->neighbors[6];
			row_start2 = row_start2->neighbors[6];
		}
		swap = head1;
		head1 = head2;
		head2 = swap;
	}

	row_start1 = head1;
	current1 = head1;
	int answer = 0;
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			answer += (current1->value == 2);
			current1 = current1->neighbors[4];
		}
		row_start1 = row_start1->neighbors[6];
		current1 = row_start1;
	}
	timer.stop();
	delete head1;
	delete head2;
	return answer;
}
