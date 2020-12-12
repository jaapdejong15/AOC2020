#include "day12.h"

int xs[] = { 0, 1, 0, -1 };
int ys[] = { 1, 0, -1, 0 };

int day12_1(Timer& timer)
{
	std::vector<std::string> input = getStringInput("input12.txt");

	int currentDirection = 1;
	int posx = 0;
	int posy = 0;
	for (std::string s : input) {
		char instruction = s[0];
		int amount = std::stoi(s.substr(1));
		switch (instruction) {
		case 'F':
			posx += xs[currentDirection] * amount;
			posy += ys[currentDirection] * amount;
			break;
		case 'L':
			currentDirection = (currentDirection - (amount / 90)) % 4;
			currentDirection = currentDirection < 0 ? currentDirection + 4 : currentDirection;
			break;
		case 'R':
			currentDirection = (currentDirection + (amount / 90)) % 4;
			break;
		case 'N':
			posy += amount;
			break;
		case 'E':
			posx += amount;
			break;
		case 'S':
			posy -= amount;
			break;
		case 'W':
			posx -= amount;
			break;
		}
	}
	return abs(posx) + abs(posy);
}

int day12_2(Timer& timer)
{
	return 0;
}
