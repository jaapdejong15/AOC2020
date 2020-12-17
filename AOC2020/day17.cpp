#include "day17.h"
#include <set>

struct Position3D {
	std::int_fast8_t x;
	std::int_fast8_t y;
	std::int_fast8_t z;

	Position3D(std::int_fast8_t x, std::int_fast8_t y, std::int_fast8_t z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
};

bool operator<(const Position3D& l, const Position3D& r) {
	return (l.x < r.x || (l.x == r.x && l.y < r.y) || (l.x == r.x && l.y == r.y && l.z < r.z));
}

bool operator==(const Position3D& l, const Position3D& r) {
	return l.x == r.x && l.y == r.y && l.z == r.z;
}

int countActiveNeighbors(Position3D pos, std::set<Position3D> &active) {
	int count = 0;
	for (int x_offset = -1; x_offset <= 1; x_offset++) {
		for (int y_offset = -1; y_offset <= 1; y_offset++) {
			for (int z_offset = -1; z_offset <= 1; z_offset++) {
				if (x_offset != 0 || y_offset != 0 || z_offset != 0) {
					count += (active.find(Position3D(pos.x + x_offset, pos.y + y_offset, pos.z + z_offset)) != active.end());
					if (count > 3) return 4;
				}
			}
		}
	}
	return count;
}

int day17_1(Timer& timer)
{
	std::vector<std::string> input = getStringInput("input17.txt");
	std::set<Position3D> active;

	timer.start();
	for (int y = 0; y < input.size(); y++) {
		for (int x = 0; x < input[y].size(); x++) {
			if (input[y][x] == '#') {
				active.insert(Position3D(x, -y, 0));
			}
		}
	}

	std::set<Position3D> nextActive;
	std::set<Position3D> positionsToCheck;
	for (int cycle = 0; cycle < 6; cycle++) {
		// Insert all neighbors of active positions in positionsToCheck
		for (Position3D pos : active) {
			for (int x_offset = -1; x_offset <= 1; x_offset++) {
				for (int y_offset = -1; y_offset <= 1; y_offset++) {
					for (int z_offset = -1; z_offset <= 1; z_offset++) {
						positionsToCheck.insert(Position3D(pos.x + x_offset, pos.y + y_offset, pos.z + z_offset));
					}
				}
			}
		}
		// Check all positions in positionsToCheck
		for (Position3D pos : positionsToCheck) {
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
	}
	timer.stop();
	return active.size();
}

struct Position4D {
	std::int_fast8_t x;
	std::int_fast8_t y;
	std::int_fast8_t z;
	std::int_fast8_t w;

	Position4D(std::int_fast8_t x, std::int_fast8_t y, std::int_fast8_t z, std::int_fast8_t w) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}
};

bool operator<(const Position4D& l, const Position4D& r) {
	return (l.x < r.x || (l.x == r.x && l.y < r.y) || (l.x == r.x && l.y == r.y && l.z < r.z) || (l.x == r.x && l.y == r.y && l.z == r.z && l.w < r.w));
}

bool operator==(const Position4D& l, const Position4D& r) {
	return l.x == r.x && l.y == r.y && l.z == r.z && l.w == r.w;
}

int countActiveNeighbors(Position4D pos, std::set<Position4D>& active) {
	int count = 0;
	for (int x_offset = -1; x_offset <= 1; x_offset++) {
		for (int y_offset = -1; y_offset <= 1; y_offset++) {
			for (int z_offset = -1; z_offset <= 1; z_offset++) {
				for (int w_offset = -1; w_offset <= 1; w_offset++) {
					if (x_offset != 0 || y_offset != 0 || z_offset != 0 || w_offset != 0) {
						count += (active.find(Position4D(pos.x + x_offset, pos.y + y_offset, pos.z + z_offset, pos.w + w_offset)) != active.end());
						if (count > 3) return 4;
					}
				}
			}
		}
	}
	return count;
}

int day17_2(Timer& timer)
{
	timer.start();
	std::vector<std::string> input = getStringInput("input17.txt");
	std::set<Position4D> active;

	for (int y = 0; y < input.size(); y++) {
		for (int x = 0; x < input[y].size(); x++) {
			if (input[y][x] == '#') {
				active.insert(Position4D(x, -y, 0, 0));
			}
		}
	}

	std::set<Position4D> nextActive;
	std::set<Position4D> positionsToCheck;
	for (int cycle = 0; cycle < 6; cycle++) {
		// Insert all neighbors of active positions in positionsToCheck
		for (Position4D pos : active) {
			for (int x_offset = -1; x_offset <= 1; x_offset++) {
				for (int y_offset = -1; y_offset <= 1; y_offset++) {
					for (int z_offset = -1; z_offset <= 1; z_offset++) {
						for (int w_offset = -1; w_offset <= 1; w_offset++) {
							positionsToCheck.insert(Position4D(pos.x + x_offset, pos.y + y_offset, pos.z + z_offset, pos.w + w_offset));
						}	
					}
				}
			}
		}
		// Check all positions in positionsToCheck
		for (Position4D pos : positionsToCheck) {
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
	}
	timer.stop();
	return active.size();
}
