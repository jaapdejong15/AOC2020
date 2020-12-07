#include "day7.h"
#include <regex>
#include <unordered_set>
#include <unordered_map>

std::vector<std::string> getInput7() {
	std::ifstream file("input7.txt");
	std::vector<std::string> lines;
	for (std::string line; std::getline(file, line);) {
		lines.push_back(line);
	}
	return lines;
}

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

void arr_printer(std::vector<std::vector<int>> arr) {
	for (std::vector<int> x : arr) {
		for (int i : x) {
			std::cout << i << " ";
		}
		std::cout << std::endl;
	}
}

void day7_1() {
	std::vector<std::string> input = getInput7();
	std::unordered_set<std::string> colorset;

	std::vector<std::tuple<std::string, std::vector<int>, std::vector<std::string>>> data;
	for (std::string line : input) {
		std::vector<std::string> words = split7(line, ' ');
		std::string outer_bag = words[0] + words[1];
		colorset.insert(outer_bag);
		std::vector<int> amounts;
		std::vector<std::string> colors;
		size_t inner_bag_id = 0;
		while (inner_bag_id < (words.size() - 4) / 4) {
			std::string color = words[5 + 4 * inner_bag_id] + words[6 + 4 * inner_bag_id];
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
	std::cout << "i = " << num_colors << std::endl;
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
	std::cout << "size: " << indices.size() << std::endl;
}