#include "helper.h"

std::vector<uint64_t> getInt64Input(std::string filename) {
	std::ifstream file(filename);
	std::vector<uint64_t> lines;
	for (std::string line; std::getline(file, line);) {
		lines.push_back(std::stoll(line));
	}
	return lines;
}

std::vector<int> getIntInput(std::string filename) {
	std::ifstream file(filename);
	std::vector<int> lines;
	for (std::string line; std::getline(file, line);) {
		lines.push_back(std::stoi(line));
	}
	return lines;
}

std::vector<std::string> getStringInput(std::string filename) {
	std::ifstream file(filename);
	std::vector<std::string> lines;
	for (std::string line; std::getline(file, line);) {
		lines.push_back(line);
	}
	return lines;
}

std::vector<std::string> splitter(std::string x, char token) {
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