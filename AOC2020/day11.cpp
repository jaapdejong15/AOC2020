#include "day11.h"

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

/*
  Constructs a 2d linked list that links to all eight of its neighbors.
*/
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

bool checkIf0Neighbors(Node* node) {
	for (int i = 0; i < 8; i++) {
		if (node->neighbors[i] != NULL && node->neighbors[i]->value == 2) return true;
	}
	return false;
}

int checkAllNeighbors(Node* node) {
	int count = 0;
	for (int i = 0; i < 8; i++) {
		count += node->neighbors[i] != NULL && node->neighbors[i]->value == 2;
	}
	return count;
}

int day11_1(Timer& timer) {
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
					seats = checkIf0Neighbors(current1);
					if (seats == 0) {
						change = true;
						current2->value = 2;
					}
					else {
						current2->value = current1->value;
					}
				}
				else if (current1->value == 2) {
					seats = checkAllNeighbors(current1);
					if (seats >= 4) {
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
