#pragma once
#include <vector>

class Grid {
public:
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

	// top left
	Node* head;

	Grid() {
		head = NULL;
	}

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
					//printf("current value: %d\n", current->value);
					//std::cout << "current neighbor 4: " << current->neighbors[3]->neighbors[4] << std::endl;
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
};
