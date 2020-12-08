#include "day8.h"
#include <unordered_set>
#include <map>

enum class instruction {
	nop,
	acc,
	jmp,
};

std::map<std::string, instruction> instruction_map;

void initialize8() {
	instruction_map["nop"] = instruction::nop;
	instruction_map["acc"] = instruction::acc;
	instruction_map["jmp"] = instruction::jmp;
}

std::vector<std::string> getInput8() {
	std::ifstream file("input8.txt");
	std::vector<std::string> lines;
	for (std::string line; std::getline(file, line);) {
		lines.push_back(line);
	}
	return lines;
}

void day8_1() {
	initialize8();
	std::vector<std::string> input = getInput8();
	int current_line = 0;
	int accumulator = 0;
	std::unordered_set<int> lines_visited;
	lines_visited.insert(0);
	int previous_size = 0;
	while (true) {
		lines_visited.insert(current_line);
		if (lines_visited.size() == previous_size) {
			break;
		}
		previous_size = lines_visited.size();
		std::string line = input[current_line];
		instruction x = instruction_map[line.substr(0, 3)];
		int argument = std::stoi(line.substr(4, 10));
		switch (x) {
		case instruction::nop:
			current_line++;
			break;
		case instruction::acc:
			accumulator += argument;
			current_line++;
			break;
		case instruction::jmp:
			current_line += argument;
			break;
		}
	}
	std::cout << "ANSWER: " << accumulator << std::endl;
}

void day8_2() {

}