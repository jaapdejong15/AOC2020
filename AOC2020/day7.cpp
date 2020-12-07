#include "day7.h"
#include <regex>
#include <unordered_set>
#include <unordered_map>

std::vector<std::string> split7(std::string x, char token) {
	std::vector<std::string> output;
	size_t start = 0;
	for (size_t i = 0; i < x.size(); i++) {
		if (x[i] == token) {
			output.push_back(x.substr(start, i - start));
			start = i + 1;
		}
	}
	output.push_back(x.substr(start, x.size() - start));
	return output;
}

class Graph {
public:
	std::vector<std::vector<int>> adjacency_matrix;
	std::unordered_map<std::string, int> color_to_index;
	std::unordered_map<int, std::string> index_to_color;
	int num_colors;

	Graph(std::vector<std::vector<int>> adjacency_matrix, std::unordered_map<std::string, int> color_to_index, std::unordered_map<int, std::string> index_to_color, int num_colors) {
		this->adjacency_matrix = adjacency_matrix;
		this->color_to_index = color_to_index;
		this->index_to_color = index_to_color;
		this->num_colors = num_colors;
	}

	Graph(std::vector<std::string> input) {
		std::unordered_set<std::string> colorset;
		std::vector<std::tuple<std::string, std::vector<int>, std::vector<std::string>>> data;
		std::string color;
		for (std::string line : input) {
			std::vector<std::string> words = split7(line, ' ');

			std::string outer_bag = words[0] + words[1];
			colorset.insert(outer_bag);

			std::vector<int> amounts;
			std::vector<std::string> colors;
			size_t inner_bag_id = 0;
			while (inner_bag_id < (words.size() - 4) / 4) {
				color = words[5 + 4 * inner_bag_id] + words[6 + 4 * inner_bag_id];
				if (color.compare("noother") != 0) {
					amounts.push_back(std::stoi(words[4 + 4 * inner_bag_id]));
					colors.push_back(color);
				}
				inner_bag_id++;
			}
			data.push_back(std::make_tuple(outer_bag, amounts, colors));
		}

		int num_colors = 0;
		std::unordered_map<std::string, int> color_to_index;
		std::unordered_map<int, std::string> index_to_color;
		for (std::string color : colorset) {
			color_to_index.insert({ color, num_colors });
			index_to_color.insert({ num_colors, color });
			num_colors++;
		}

		std::vector<std::vector<int>> adjacency_matrix;
		for (int i = 0; i < num_colors; i++) {
			adjacency_matrix.push_back(std::vector<int>(num_colors, 0));
		}

		for (std::tuple<std::string, std::vector<int>, std::vector<std::string>> tuple : data) {
			int index1 = color_to_index[std::get<0>(tuple)];
			for (int j = 0; j < std::get<1>(tuple).size(); j++) {
				int index2 = color_to_index[std::get<2>(tuple)[j]];
				adjacency_matrix[color_to_index[std::get<0>(tuple)]][color_to_index[std::get<2>(tuple)[j]]] = std::get<1>(tuple)[j];
			}
		}
		this->adjacency_matrix = adjacency_matrix;
		this->color_to_index = color_to_index;
		this->index_to_color = index_to_color;
		this->num_colors = num_colors;
	}

	std::unordered_set<int> bags_that_contain(std::string color) {
		std::unordered_set<int> unexplored;
		std::unordered_set<int> indices;
		int gold_index = color_to_index["shinygold"];
		for (int i = 0; i < num_colors; i++) {
			if (adjacency_matrix[i][gold_index] != 0) {
				unexplored.insert(i);
				indices.insert(i);
			}
		}
		while (unexplored.size() != 0) {
			std::unordered_set<int> new_unexplored;
			for (int index : unexplored) {
				for (int i = 0; i < num_colors; i++) {
					if (adjacency_matrix[i][index] != 0) {
						new_unexplored.insert(i);
						indices.insert(i);
					}
				}
			}
			unexplored = new_unexplored;
		}
		return indices;
	}

	int count_bags_inside(std::string color) {
		int bag_id = color_to_index[color];
		return count_bags_inside(bag_id) - 1; // Don't include the outer bag
	}

	int count_bags_inside(int bag_id) {
		int count = 1;
		for (int i = 0; i < adjacency_matrix[0].size(); i++) {
			if (adjacency_matrix[bag_id][i] != 0) {
				count += adjacency_matrix[bag_id][i] * count_bags_inside(i);
			}
		}
		return count;
	}
};

std::vector<std::string> getInput7() {
	std::ifstream file("input7.txt");
	std::vector<std::string> lines;
	for (std::string line; std::getline(file, line);) {
		lines.push_back(line);
	}
	return lines;
}

void day7_1() {
	std::vector<std::string> input = getInput7();

	auto start = std::chrono::high_resolution_clock::now();

	Graph g = Graph(input);
	std::unordered_set<int> indices = g.bags_that_contain("shinygold");

	auto stop = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> time = stop - start;
	printf("==========\nPART 1\nAnswer:        %d\nCalculated in: %f ms\n==========\n", indices.size(), time.count());
}

void day7_2() {
	std::vector<std::string> input = getInput7();

	auto start = std::chrono::high_resolution_clock::now();

	Graph g = Graph(input);
	int count = g.count_bags_inside("shinygold");

	auto stop = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> time = stop - start;
	printf("==========\nPART 2\nAnswer:        %d\nCalculated in: %f ms\n==========\n", count, time.count());
}