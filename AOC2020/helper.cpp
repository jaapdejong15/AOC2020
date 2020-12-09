#include "helper.h"

std::vector<uint64_t> getInt64Input(std::string filename) {
	std::ifstream file(filename);
	std::vector<uint64_t> lines;
	for (std::string line; std::getline(file, line);) {
		lines.push_back(std::stoll(line));
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