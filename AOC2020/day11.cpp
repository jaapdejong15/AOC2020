#include "day11.h"

struct Node {
	int_fast8_t value;
	/*
	0 1 2
	3 . 4
	5 6 7
	*/
	Node* neighbors[8];

	~Node() {
		delete neighbors[4];
		if (neighbors[3] == NULL) {
			delete neighbors[6];
		}
	}
};

Node* getGrid(std::vector<std::vector<int>> input) {
	Node* head = NULL;
	Node* pos3 = NULL;
	Node* pos0 = NULL;
	Node* pos1 = NULL;
	Node* pos2 = NULL;
	Node* first_node_of_row;

	head = new Node();
	head->value = input[0][0];
	pos3 = head;
	first_node_of_row = head;

	bool very_first_value = true;
	bool first_row = true;
	Node* current;
	for (std::vector<int> row : input) {
		for (int i : row) {
			if (very_first_value) {
				very_first_value = false;
			}
			else {
				current = new Node();
				current->value = i;
				current->neighbors[3] = pos3;
				if (pos3 != NULL) {
					pos3->neighbors[4] = current;
				}
				pos3 = current;
				current->neighbors[0] = pos0;
				if (pos0 != NULL) {
					pos0->neighbors[7] = current;
				}
				current->neighbors[1] = pos1;
				if (pos1 != NULL) {
					pos1->neighbors[6] = current;
				}

				pos0 = pos1;
				pos1 = pos2;
				current->neighbors[2] = pos2;
				if (pos2 != NULL) {
					pos2->neighbors[5] = current;
					pos2 = pos2->neighbors[4];
				}
			}

		}

		if (first_node_of_row->neighbors[6] != NULL) first_node_of_row = first_node_of_row->neighbors[6];
		pos0 = NULL;
		pos1 = first_node_of_row;
		pos2 = first_node_of_row->neighbors[4];
		pos3 = NULL;

	}
	return head;
}

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

int checkAllDirections(Node* current_node) {
	int count = 0;
	Node* next_node;
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

int checkIf0Directions(Node* current_node) {
	Node* next_node;
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

int day11_2(Timer& timer) {
	std::vector<std::vector<int>> input = getInput11("input11.txt");
	timer.start();
	
	int width = input[0].size();
	int height = input.size();

	bool change = true;
	Node* head1 = getGrid(input);
	Node* head2 = getGrid(input); 
	Node* swap;
	Node* row_start1 = head1;
	Node* row_start2 = head2;
	Node* current1 = head1;
	Node* current2 = head2;
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
