#include "day2.h"

int day2_1(Timer &timer) {
	std::vector<std::string> input = getStringInput("input2.txt");

	timer.start();

	int answer = 0;
	for (std::string line : input) {
		size_t pos1 = line.find('-');
		size_t pos2 = line.find(' ');
		size_t pos3 = line.find(": ");
		int minimum = std::stoi(line.substr(0, pos1));
		int maximum = std::stoi(line.substr(pos1 + 1, pos2 - pos1 - 1));
		std::string character = line.substr(pos2 + 1, 1);
		std::string password = line.substr(pos3 + 1, line.size() - pos3);
		int count = std::count(password.begin(), password.end(), character[0]);
		if (count <= maximum && count >= minimum) {
			answer++;
		}
	}

	timer.stop();
	return answer;
}

int day2_2(Timer &timer) {
	std::vector<std::string> input = getStringInput("input2.txt");

	timer.start();

	int answer = 0;
	for (std::string line : input) {
		size_t pos1 = line.find('-');
		size_t pos2 = line.find(' ');
		size_t pos3 = line.find(": ");
		char character = line.substr(pos2 + 1, 1)[0];
		
		char char1 = line[std::stoi(line.substr(0, pos1)) + pos3 + 1];
		char char2 = line[std::stoi(line.substr(pos1 + 1, pos2)) + pos3 + 1];
		if ((char1 == character) ^ (char2 == character)) {
			answer++;
		}
	}
	timer.stop();
	return answer;
}