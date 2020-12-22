#include "day22.h"
#include <queue>
#include <deque>
#include <unordered_set>
#include <sstream>

unsigned long long day22_1(Timer& timer)
{
	std::vector<std::string> input = getStringInput("input22.txt");
	std::queue<int> player1deck;
	std::queue<int> player2deck;

	bool player1 = true;
	int i = 1;
	for (; ; i++) {
		if (input[i].size() == 0) break;
		player1deck.push(std::stoi(input[i]));
	}
	i += 2;
	for (; i < input.size(); i++) player2deck.push(std::stoi(input[i]));

	int p1card;
	int p2card;
	int roundCounter = 0;
	while (!player1deck.empty() && !player2deck.empty()) {
		roundCounter++;
		p1card = player1deck.front();
		p2card = player2deck.front();
		player1deck.pop();
		player2deck.pop();
		if (p1card > p2card) {
			player1deck.push(p1card);
			player1deck.push(p2card);
		}
		else {
			player2deck.push(p2card);
			player2deck.push(p1card);
		}
	}

	printf("Winner: %d\nNum rounds: %d\n", 1 + player1deck.empty(), roundCounter);
	unsigned long long answer = 0;
	if (player1deck.empty()) {
		for (int j = player2deck.size(); j >= 1; j--) {
			answer += j * player2deck.front();
			player2deck.pop();
		}
	}
	else {
		for (int j = player1deck.size(); j >= 1; j--) {
			answer += j * player1deck.front();
			player1deck.pop();
		}
	}


	return answer;
}

std::string createConfiguration(std::deque<int> p1cards, std::deque<int> p2cards) {
	std::stringstream config;
	for (int i = 0; i < p1cards.size(); i++) {
		config << p1cards.front();
		config << ',';
		p1cards.pop_front();
	}
	config << "|";
	for (int i = 0; i < p2cards.size(); i++) {
		config << p2cards.front();
		config << ',';
		p2cards.pop_front();
	}
	return config.str();
}

void printDeque(std::deque<int> x) {
	for (int y : x) {
		std::cout << y << " ";
	}
	std::cout << std::endl;
}


// If toplevel = false, it returns 0 if 1 wins and 1 if 2 wins. Otherwise it returns the winning players score
unsigned int playRecursiveCombat(std::deque<int> player1deck, std::deque<int> player2deck, bool topGame = false) {
	std::unordered_set<std::string> previousConfigurations;

	int p1card;
	int p2card;
	bool recursiveProtection = false;
	while (!player1deck.empty() && !player2deck.empty()) {
		//std::cout << "P1: ";
		//printDeque(player1deck);

		//std::cout << "P2: ";
		//printDeque(player2deck);

		std::string configuration = createConfiguration(player1deck, player2deck);
		//std::cout << configuration.c_str() << std::endl;
		if (previousConfigurations.find(configuration) != previousConfigurations.end()) {
			recursiveProtection = true;
			break;
		}
		previousConfigurations.insert(configuration);

		p1card = player1deck.front();
		p2card = player2deck.front();
		player1deck.pop_front();
		player2deck.pop_front();
		bool p2_is_winner;
		if (p1card > player1deck.size() || p2card > player2deck.size()) {
			p2_is_winner = p1card < p2card;
		}
		else {
			std::deque<int> p1new_deck(player1deck.begin(), player1deck.begin() + p1card);
			std::deque<int> p2new_deck(player2deck.begin(), player2deck.begin() + p2card);
			p2_is_winner = playRecursiveCombat(p1new_deck, p2new_deck);
		}

		if (p2_is_winner) {
			player2deck.push_back(p2card);
			player2deck.push_back(p1card);
		}
		else {
			player1deck.push_back(p1card);
			player1deck.push_back(p2card);
		}
	}

	if (recursiveProtection) {
		// P1 wins
		if (topGame) {
			int answer = 0;
			for (int j = player1deck.size(); j >= 1; j--) {
				answer += j * player1deck.front();
				player1deck.pop_front();
			}
			return answer;
		}
		else return 0;

	}
	else {
		if (topGame) {
			int answer = 0;
			if (player1deck.empty()) {
				// Player 2 wins
				for (int j = player2deck.size(); j >= 1; j--) {
					answer += j * player2deck.front();
					player2deck.pop_front();
				}
			}
			else {
				// Player 1 wins
				for (int j = player1deck.size(); j >= 1; j--) {
					answer += j * player1deck.front();
					player1deck.pop_front();
				}
			}
			return answer;
		}
		else return player1deck.empty();
	}
}

unsigned long long day22_2(Timer& timer)
{

	std::vector<std::string> input = getStringInput("input22.txt");
	std::deque<int> player1deck;
	std::deque<int> player2deck;

	timer.start();
	bool player1 = true;
	int i = 1;
	for (; ; i++) {
		if (input[i].size() == 0) break;
		player1deck.push_back(std::stoi(input[i]));
	}
	i += 2;
	for (; i < input.size(); i++) player2deck.push_back(std::stoi(input[i]));

	unsigned int answer = playRecursiveCombat(player1deck, player2deck, true);

	timer.stop();
	return answer;
}
