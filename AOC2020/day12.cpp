#include "day12.h"

int xs[] = { 0, 1, 0, -1 };
int ys[] = { 1, 0, -1, 0 };

int day12_1(Timer& timer)
{
	std::vector<std::string> input = getStringInput("input12.txt");

	timer.start();
	size_t currentDirection = 1;
	int posx = 0;
	int posy = 0;
	int amount;
	char instruction;
	for (std::string s : input) {
		instruction = s[0];
		amount = std::stoi(s.substr(1));
		switch (instruction) {
		case 'F':
			posx += xs[currentDirection] * amount;
			posy += ys[currentDirection] * amount;
			break;
		case 'L':
			currentDirection = (currentDirection - (amount / 90) + 4) % 4;
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
	int answer = abs(posx) + abs(posy);
	timer.stop();
	return answer;
}

int day12_2(Timer& timer)
{
	std::vector<std::string> input = getStringInput("input12.txt");

	timer.start();
	int waypoint_x = 10;
	int waypoint_y = 1;
	int ship_x = 0;
	int ship_y = 0;
	char instruction;
	int amount; 
	int swap;
	for (std::string s : input) {
		instruction = s[0];
		amount = std::stoi(s.substr(1));
		swap;
		switch (instruction) {
		case 'F':
			ship_x += waypoint_x * amount;
			ship_y += waypoint_y * amount;
			break;
		case 'L':
			for (int i = 0; i < amount / 90; i++) {
				waypoint_y = -waypoint_y;
				swap = waypoint_x;
				waypoint_x = waypoint_y;
				waypoint_y = swap;
			}
			break;
		case 'R':
			for (int i = 0; i < amount / 90; i++) {
				waypoint_x = -waypoint_x;
				swap = waypoint_x;
				waypoint_x = waypoint_y;
				waypoint_y = swap;
			}
			break;
		case 'N':
			waypoint_y += amount;
			break;
		case 'E':
			waypoint_x += amount;
			break;
		case 'S':
			waypoint_y -= amount;
			break;
		case 'W':
			waypoint_x -= amount;
			break;
		}
	}
	int answer = abs(ship_x) + abs(ship_y);
	timer.stop();
	return answer;
}
