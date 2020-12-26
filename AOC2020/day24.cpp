#include "day24.h"
#include <set>

unsigned long long day24_1(Timer& timer)
{
	std::vector<std::string> input = getStringInput("input24.txt");
	std::set<std::pair<int, int>> floor;

	for (std::string line : input) {
		int x = 0;
		int y = 0;
		char lastChar = 'x';
		for (char c : line) {
			switch (lastChar) {
			case 'n':
				y++;
				switch (c) {
				case 'e':
					if (y % 2 == 0) x++;
					lastChar = 'e';
					break;
				case 'w':
					if (y % 2 != 0) x--;
					lastChar = 'w';
					break;
				}
				break;
			case 's':
				y--;
				switch (c) {
				case 'e':
					if (y % 2 == 0) x++;
					lastChar = 'e';
					break;
				case 'w':
					if (y % 2 != 0) x--;
					lastChar = 'w';
					break;
				}
				break;
			default:
				switch (c) {
				case 'n':
					lastChar = 'n';
					break;
				case 'e':
					lastChar = 'e';
					x++;
					break;
				case 's':
					lastChar = 's';
					break;
				case 'w':
					lastChar = 'w';
					x--;
					break;
				default: 
					break;
				}
				break;
			}
		}
		std::pair<int, int> location = std::make_pair(x, y);
		if (floor.find(location) == floor.end()) {
			floor.insert(location);
		}
		else {
			floor.erase(location);
		}
	}
	return floor.size();
}

unsigned long long day24_2(Timer& timer)
{
	std::vector<std::string> input = getStringInput("input24.txt");
	std::set<std::pair<int, int>> floor;

	// Get floor
	for (std::string line : input) {
		int x = 0;
		int y = 0;
		char lastChar = 'x';
		for (char c : line) {
			switch (lastChar) {
			case 'n':
				y++;
				switch (c) {
				case 'e':
					if (y % 2 == 0) x++;
					lastChar = 'e';
					break;
				case 'w':
					if (y % 2 != 0) x--;
					lastChar = 'w';
					break;
				}
				break;
			case 's':
				y--;
				switch (c) {
				case 'e':
					if (y % 2 == 0) x++;
					lastChar = 'e';
					break;
				case 'w':
					if (y % 2 != 0) x--;
					lastChar = 'w';
					break;
				}
				break;
			default:
				switch (c) {
				case 'n':
					lastChar = 'n';
					break;
				case 'e':
					lastChar = 'e';
					x++;
					break;
				case 's':
					lastChar = 's';
					break;
				case 'w':
					lastChar = 'w';
					x--;
					break;
				default:
					break;
				}
				break;
			}
		}
		std::pair<int, int> location = std::make_pair(x, y);
		if (floor.find(location) == floor.end()) {
			floor.insert(location);
		}
		else {
			floor.erase(location);
		}
	}

	for (int i = 0; i < 100; i++) {
		std::set<std::pair<int, int>> tilesToCheck;
		for (std::pair<int, int> loc : floor) {
			tilesToCheck.insert(std::make_pair(loc.first + 1, loc.second));
			tilesToCheck.insert(std::make_pair(loc.first - 1, loc.second));
			tilesToCheck.insert(std::make_pair(loc.first + (loc.second % 2 != 0), loc.second + 1));
			tilesToCheck.insert(std::make_pair(loc.first + (loc.second % 2 != 0), loc.second - 1));
			tilesToCheck.insert(std::make_pair(loc.first - (loc.second % 2 == 0), loc.second + 1));
			tilesToCheck.insert(std::make_pair(loc.first - (loc.second % 2 == 0), loc.second - 1));
		}
		std::set<std::pair<int, int>> newFloor;
		for (std::pair<int, int> loc : tilesToCheck) {
			int numTiles
				= (floor.find(std::make_pair(loc.first + 1, loc.second)) != floor.end())
				+ (floor.find(std::make_pair(loc.first - 1, loc.second)) != floor.end())
				+ (floor.find(std::make_pair(loc.first + (loc.second % 2 != 0), loc.second + 1)) != floor.end())
				+ (floor.find(std::make_pair(loc.first + (loc.second % 2 != 0), loc.second - 1)) != floor.end())
				+ (floor.find(std::make_pair(loc.first - (loc.second % 2 == 0), loc.second + 1)) != floor.end())
				+ (floor.find(std::make_pair(loc.first - (loc.second % 2 == 0), loc.second - 1)) != floor.end());
			if (floor.find(loc) == floor.end()) {
				// Tile is white
				if (numTiles == 2) newFloor.insert(loc);
			}
			else {
				// Tile is black
				if (numTiles == 1 || numTiles == 2) newFloor.insert(loc);
			}
		}
		floor = newFloor;
	}

	return floor.size();
}
