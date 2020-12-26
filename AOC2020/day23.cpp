#include "day23.h"

#define NUM_CUPS 1000000
#define ITERATIONS 10000000

struct CircularListNode {
	CircularListNode* prev;
	CircularListNode* next;
	uint_fast8_t x;

	CircularListNode(uint_fast8_t x) {
		this->x = x;
		prev = NULL;
		next = NULL;
	}

	~CircularListNode() {
		if (prev != NULL) prev->next = NULL;
		delete next;
	}
};

struct CircularListNode2 {
	CircularListNode2* next;
	int x;

	CircularListNode2(int x) {
		this->x = x;
		next = NULL;
	}
};

std::string day23_1(Timer& timer)
{
	std::vector<uint_fast8_t> input = { 7, 9, 2, 8, 4, 5, 1, 3, 6 };

	CircularListNode* head = new CircularListNode(input[0]);
	CircularListNode* previous = head;

	for (int i = 1; i < input.size(); i++) {
		CircularListNode *current = new CircularListNode(input[i]);
		previous->next = current;
		current->prev = previous;
		previous = current;
	}
	head->prev = previous;
	previous->next = head;


	CircularListNode* currentCup = head;
	CircularListNode* cup1;
	CircularListNode* cup3;
	CircularListNode* destinationCup;
	for (int i = 0; i < 100; i++) {
		cup1 = currentCup->next;
		cup3 = cup1->next->next;

		// Remove next three cups;
		currentCup->next = cup3->next;
		cup3->next->prev = currentCup;

		// Find destination cup
		int valueToFind = (currentCup->x + 7) % 9 + 1;
		CircularListNode* searchCup = cup3->next;
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

	delete currentCup;

	return answer;
}

unsigned long long day23_2(Timer& timer)
{
	std::vector<uint_fast8_t> input = { 7, 9, 2, 8, 4, 5, 1, 3, 6 };

	CircularListNode2* head = new CircularListNode2(input[0]);
	CircularListNode2* previous = head;

	CircularListNode2* cupWith1 = head;

	std::vector<CircularListNode2*> nodeMap(NUM_CUPS + 1, NULL);
	nodeMap[input[0]] = head;

	timer.start();

	// Create initial list
	for (int i = 1; i < input.size(); i++) {
		CircularListNode2* current = new CircularListNode2(input[i]);
		previous->next = current;
		if (input[i] == 1) cupWith1 = current;
		nodeMap[input[i]] = current;
		previous = current;
	}
	
	// Create cups until 1 million is reached
	for (int i = input.size() + 1; i <= NUM_CUPS; i++) {
		CircularListNode2* current = new CircularListNode2(i);
		previous->next = current;
		nodeMap[i] = current;
		previous = current;
	}

	previous->next = head;

	CircularListNode2* currentCup = head;
	CircularListNode2* cup1; 
	CircularListNode2* cup3;
	CircularListNode2* destinationCup;
	int val1, val2, val3;
	for (int i = 0; i < ITERATIONS; i++) {
		cup1 = currentCup->next;
		cup3 = cup1->next->next;
		val1 = cup1->x;
		val2 = cup1->next->x;
		val3 = cup3->x;

		// Remove next three cups;
		currentCup->next = cup3->next;

		// Find destination cup
		int valueToFind = currentCup->x - 1;
		if (valueToFind == 0) valueToFind = NUM_CUPS;
		while (true) {
			if (valueToFind == val1 || valueToFind == val2 || valueToFind == val3) {
				valueToFind--;
				if (!valueToFind) valueToFind = NUM_CUPS;
			}
			else break;
		}

		destinationCup = nodeMap[valueToFind];

		// Move the three cups
		cup3->next = destinationCup->next;
		destinationCup->next = cup1;

		// Select current cup
		currentCup = currentCup->next;
	}
	unsigned long long answer = (unsigned long long)cupWith1->next->x * (unsigned long long)cupWith1->next->next->x;

	timer.stop();

	// Delete nodes from the memory
	for (int i = 1; i <= NUM_CUPS; i++) {
		delete nodeMap[i];
	}

	return answer;
}
