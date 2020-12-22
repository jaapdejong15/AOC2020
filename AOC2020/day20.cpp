#include "day20.h"
#include <unordered_map>
#include <set>

enum class Side {top, top_inv, right, right_inv, bottom, bottom_inv, left, left_inv};

struct Tile {
	Tile* top;
	Tile* left;
	Tile* right;
	Tile* bottom;
	int id;

	Tile(int id) {
		this->id = id;
	}
};

std::pair<uint_fast16_t, uint_fast16_t> getEdge(std::vector<std::vector<bool>> grid, Side s) {
	uint_fast16_t edge = 0;
	switch (s) {
	case Side::top:
		for (bool x : grid[0]) {
			edge <<= 1;
			edge |= x;
		}
		break;
	case Side::bottom:
		for (bool x : grid[grid.size() - 1]) {
			edge <<= 1;
			edge |= x;
		}
		break;
	case Side::left:
		for (int i = 0; i < grid.size(); i++) {
			edge <<= 1;
			edge |= grid[i][0];
		}
		break;
	case Side::right: 
		for (int i = 0; i < grid.size(); i++) {
			edge <<= 1;
			edge |= grid[i][grid[0].size() - 1];
		}
		break;
	default:
		break;
	}
	uint_fast16_t reverse_edge = 0;
	for (int i = 0; i < 10; i++) {
		reverse_edge <<= 1;
		reverse_edge |= edge >> i & 1;
	}
	return std::make_pair(edge, reverse_edge);
}

std::pair<std::unordered_map<int, std::vector<std::vector<bool>>>, std::set<int>> getTiles(std::vector<std::string> input) {
	std::unordered_map<int, std::vector<std::vector<bool>>> tiles;
	std::vector<std::vector<bool>> currentTile;
	std::set<int> ids;
	uint_fast16_t currentId = 0;
	for (std::string line : input) {
		if (line.size() == 0) {
			tiles[currentId] = currentTile;
			currentTile.clear();
		}
		else if (line[0] == 'T') {
			currentId = std::stoi(line.substr(5, 4));
			ids.insert(currentId);
			currentTile.clear();
		} 
		else {
			std::vector<bool> row;
			for (char c : line) {
				switch (c) {
				case '#':
					row.push_back(true);
					break;
				case '.':
					row.push_back(false);
					break;
				}
			}
			currentTile.push_back(row);
		}
	}
	tiles[currentId] = currentTile;
	return std::make_pair(tiles, ids);
}

void storeEdges(Side s1, Side s1_inv, std::unordered_map<uint_fast16_t, std::vector<std::pair<uint_fast16_t, Side>>>& edgeToID, std::unordered_map<uint_fast16_t, std::vector<std::pair<uint_fast16_t, Side>>>& IDtoEdge, std::vector<std::vector<bool>>& grid, uint_fast16_t id) {
	std::pair<uint_fast16_t, uint_fast16_t> found_edges = getEdge(grid, s1);
	edgeToID[found_edges.first].push_back(std::make_pair(id, s1));
	edgeToID[found_edges.second].push_back(std::make_pair(id, s1_inv));
	IDtoEdge[id].push_back(std::make_pair(found_edges.first, s1));
	IDtoEdge[id].push_back(std::make_pair(found_edges.first, s1_inv));
}

unsigned long long day20_1(Timer& timer)
{
	std::vector<std::string> input = getStringInput("input20.txt");
	std::pair<std::unordered_map<int, std::vector<std::vector<bool>>>, std::set<int>> parsed = getTiles(input);

	std::unordered_map<int, std::vector<std::vector<bool>>> tiles = parsed.first;
	std::set<int> ids = parsed.second;

	std::unordered_map<uint_fast16_t, std::vector<std::pair<uint_fast16_t, Side>>> edgeToID;
	std::unordered_map<uint_fast16_t, std::vector<std::pair<uint_fast16_t, Side>>> IDtoEdge;

	for (uint_fast16_t id : ids) {
		std::vector<std::vector<bool>> grid = tiles[id];
		std::cout << "Grid size: " << grid.size() << " ID: " << id << std::endl;

		storeEdges(Side::top, Side::top_inv, edgeToID, IDtoEdge, grid, id);
		storeEdges(Side::bottom, Side::bottom_inv, edgeToID, IDtoEdge, grid, id);
		storeEdges(Side::left, Side::left_inv, edgeToID, IDtoEdge, grid, id);
		storeEdges(Side::right, Side::right_inv, edgeToID, IDtoEdge, grid, id);
	}
	unsigned long long answer = 1;
	for (int i : ids) {
		int countEdges = 0;
		for (std::pair<uint_fast16_t, Side> side : IDtoEdge[i]) {
			countEdges += edgeToID[side.first].size();
		}
		if (countEdges == 12) {
			answer *= i;
		}
		
	}
	return answer;
}

void crop(std::vector<std::vector<bool>> &input) {
	input.erase(input.begin());
	input.pop_back();
	for (int i = 0; i < input.size(); i++) {
		input[i].erase(input[i].begin());
		input[i].pop_back();
	}
}

std::vector<std::vector<bool>> rotate(std::vector<std::vector<bool>> input, Side s) {
	std::vector<std::vector<bool>> output;
	switch (s) {
	case Side::left:
		// Rotate 90:
		for (int y = 0; y < input.size(); y++) {
			std::vector<bool> row;
			for (int x = 0; x < input.size(); x++) {
				row.push_back(input[7 - x][y]);
			}
			output.push_back(row);
		}
		break;
	case Side::right:
		// Rotate -90:
		for (int y = 0; y < input.size(); y++) {
			std::vector<bool> row;
			for (int x = 0; x < input.size(); x++) {
				row.push_back(input[x][7 - y]);
			}
			output.push_back(row);
		}
		break;
	case Side::bottom:
		// Rotate 180:
		for (int y = 0; y < input.size(); y++) {
			std::vector<bool> row;
			for (int x = 0; x < input.size(); x++) {
				row.push_back(input[7 - y][7 - x]);
			}
			output.push_back(row);
		}
		break;
	default:
		output = input;
		break;
	}
	return output;
}


unsigned long long day20_2(Timer& timer)
{
	std::vector<std::string> input = getStringInput("input20.txt");
	std::pair<std::unordered_map<int, std::vector<std::vector<bool>>>, std::set<int>> parsed = getTiles(input);

	std::unordered_map<int, std::vector<std::vector<bool>>> tiles = parsed.first;
	std::set<int> ids = parsed.second;

	/*
	crop(tiles[2897]);
	std::vector<std::vector<bool>> test = rotate(tiles[2897], Side::right);
	for (std::vector<bool> x : test) {
		for (bool y : x) {
			std::cout << (y ? '#' : ' ');
		}
		std::cout << '|' <<std::endl;
	}
	*/

	std::unordered_map<uint_fast16_t, std::vector<std::pair<uint_fast16_t, Side>>> edgeToID;
	std::unordered_map<uint_fast16_t, std::vector<std::pair<uint_fast16_t, Side>>> IDtoEdge;

	for (uint_fast16_t id : ids) {
		std::vector<std::vector<bool>> grid = tiles[id];

		storeEdges(Side::top, Side::top_inv, edgeToID, IDtoEdge, grid, id);
		storeEdges(Side::bottom, Side::bottom_inv, edgeToID, IDtoEdge, grid, id);
		storeEdges(Side::left, Side::left_inv, edgeToID, IDtoEdge, grid, id);
		storeEdges(Side::right, Side::right_inv, edgeToID, IDtoEdge, grid, id);
	}

	std::unordered_map<std::pair<int, int>, std::pair<int, Side>> posToTile;
	std::unordered_map<int, std::pair<std::pair<int, int>, Side>> tileToPos;

	int startId = *ids.begin();
	int lastId = startId;
	int x = 0;

	std::unordered_map<int, Tile> piecesMatched;
	for (int id : ids) {
		Tile t(id);
		tiles[id] = t;
	}

	return 0;
}
