#include "day23.h"

struct Node {
	Node* prev;
	Node* next;
	uint_fast8_t x;

	Node(uint_fast8_t x) {
		this->x = x;
		prev = NULL;
		next = NULL;
	}

	~Node() {
		if (prev != NULL) prev->next = NULL;
		delete next;
	}
};

std::string day23_1(Timer& timer)
{
	std::vector<uint_fast8_t> input = { 7, 9, 2, 8, 4, 5, 1, 3, 6 };

	std::vector<uint_fast8_t> positions(9);

	Node* head = new Node(input[0]);
	Node* previous = head;
	
	for (int i = 1; i < input.size(); i++) {
		Node *current = new Node(input[i]);
		previous->next = current;
		current->prev = previous;
		previous = current;
	}
	head->prev = previous;
	previous->next = head;

	Node* currentCup = head;
	Node* cup1;
	Node* cup3;
	Node* destinationCup;
	for (int i = 0; i < 100; i++) {
		cup1 = currentCup->next;
		cup3 = cup1->next->next;

		// Remove next three cups;
		currentCup->next = cup3->next;
		cup3->next->prev = currentCup;

		// Find destination cup
		int valueToFind = (currentCup->x + 7) % 9 + 1;
		Node* searchCup = cup3->next;
		while (true) {
			if (searchCup->x == valueToFind) {
				destinationCup = searchCup;
				break;
			}
			if (searchCup->x == currentCup->x) valueToFind = (valueToFind + 7) % 9 + 1;
			searchCup = searchCup->next;
		}

		// Move the three cups
		cup3->next = destinationCup->next;
		destinationCup->next->prev = cup3;
		cup1->prev = destinationCup;
		destinationCup->next = cup1;

		// Select current cup
		currentCup = currentCup->next;
	}

	while (currentCup->x != 1) currentCup = currentCup->next;
	std::string answer = "";
	currentCup = currentCup->next;
	while (currentCup->x != 1) {
		answer += std::to_string(currentCup->x);
		currentCup = currentCup->next;
	}
	return answer;
}

unsigned long long day23_2(Timer& timer)
{
	return 0;
}
