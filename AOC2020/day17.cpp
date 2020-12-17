#include "day17.h"
#include <set>

struct Position {
	std::int_fast8_t x;
	std::int_fast8_t y;
	std::int_fast8_t z;

	Position(std::int_fast8_t x, std::int_fast8_t y, std::int_fast8_t z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
};

bool operator<(const Position& l, const Position& r) {
	return (l.x < r.x || (l.x == r.x && l.y < r.y) || (l.x == r.x && l.y == r.y && l.z < r.z));
}

bool operator==(const Position& l, const Position& r) {
	return l.x == r.x && l.y == r.y && l.z == r.z;
}

void printer(std::set<Position>& active, int z) {
	for (int y = 3; y >= -3; y--) {
		for (int x = -3; x <= 3; x++) {
			std::cout << (active.find(Position(x, y, z)) == active.end() ? '.' : '#');
		}
		std::cout << std::endl;
	}
}

int countActiveNeighbors(Position pos, std::set<Position> &active) {
	int count = 0;
	//printf("Active size: %d\n", active.size());
	for (int x_offset = -1; x_offset <= 1; x_offset++) {
		for (int y_offset = -1; y_offset <= 1; y_offset++) {
			for (int z_offset = -1; z_offset <= 1; z_offset++) {
				if (x_offset != 0 || y_offset != 0 || z_offset != 0) {
					count += (active.find(Position(pos.x + x_offset, pos.y + y_offset, pos.z + z_offset)) != active.end());
				}
			}
		}
	}
	//printf("count for  (%d, %d, %d): %d\n", pos.x, pos.y, pos.z, count);
	return count;
}

int day17_1(Timer& timer)
{
	std::vector<std::string> input = getStringInput("input17.txt");
	std::set<Position> active;


	for (int y = 0; y < input.size(); y++) {
		for (int x = 0; x < input[y].size(); x++) {
			if (input[y][x] == '#') {
				active.insert(Position(x, -y, 0));
			}
		}
	}
	//printf("Active size: %d\n", active.size());

	std::set<Position> nextActive;
	std::set<Position> positionsToCheck;
	printer(active, 0);
	for (int cycle = 0; cycle < 6; cycle++) {
		// Insert all neighbors of active positions in positionsToCheck
		for (Position pos : active) {
			for (int x_offset = -1; x_offset <= 1; x_offset++) {
				for (int y_offset = -1; y_offset <= 1; y_offset++) {
					for (int z_offset = -1; z_offset <= 1; z_offset++) {
						positionsToCheck.insert(Position(pos.x + x_offset, pos.y + y_offset, pos.z + z_offset));
					}
				}
			}
		}
		// Check all positions in positionsToCheck
		for (Position pos : positionsToCheck) {
			int num = countActiveNeighbors(pos, active);
			if (active.find(pos) == active.end() && num == 3) {
				nextActive.insert(pos);
			}
			else if (active.find(pos) != active.end() && (num == 2 || num == 3)) {
				nextActive.insert(pos);
			}
		}
		active = nextActive;
		nextActive.clear();
		positionsToCheck.clear();
		//printer(active, -1);
	}
	
	return active.size();
}

int day17_2(Timer& timer)
{
	return 0;
}
