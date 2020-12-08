#include "day8.h"
#include <unordered_set>
#include <map>
#include <tuple>

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

std::tuple<bool, int> run(std::vector <std::tuple<instruction, int>> program) {
	int current_line = 0;
	int accumulator = 0;
	std::unordered_set<int> lines_visited;
	int previous_size = 0;
	bool terminated = true;
	while (current_line < program.size()) {
		lines_visited.insert(current_line);
		if (lines_visited.size() == previous_size) {
			terminated = false;
			break;
		}
		previous_size = lines_visited.size();
		std::tuple<instruction, int> line = program[current_line];
		instruction x = std::get<0>(line);
		int argument = std::get<1>(line);
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
	return std::make_tuple(terminated, accumulator);
}

void day8_2() {
	initialize8();
	std::vector<std::string> input = getInput8();

	std::vector<std::tuple<instruction, int>> program;
	for (std::string line : input) {
		instruction x = instruction_map[line.substr(0, 3)];
		int argument = std::stoi(line.substr(4, 10));
		program.push_back(std::make_tuple(x, argument));
	}

	int answer = 0;
	std::tuple<bool, int> results;
	for (int i = 0; i < program.size(); i++) {
		std::tuple<instruction, int> line = program[i];
		instruction x = std::get<0>(line);
		int argument = std::get<1>(line);
		switch (x) {
		case instruction::nop:
			program[i] = std::make_tuple(instruction::jmp, argument);
			results = run(program);

			if (std::get<0>(results)) {
				answer = std::get<1>(results);
			}
			program[i] = std::make_tuple(instruction::nop, argument);
			
			break;
		case instruction::jmp:
			program[i] = std::make_tuple(instruction::nop, argument);
			results = run(program);
			if (std::get<0>(results)) {
				answer = std::get<1>(results);
			}
			program[i] = std::make_tuple(instruction::jmp, argument);
			break;
		default:
			break;
		}
	}

	std::cout << "ANSWER: " << answer << std::endl;
}