#include "day4.h"
#include <numeric>
#include <map>
#include <sstream>
#include <iterator>
#include <regex>

enum class field {
	byr, 
	iyr,
	eyr,
	hgt,
	hcl,
	ecl,
	pid,
	cid
};

std::map<std::string, field> field_map;

void initialize() {
	field_map["byr"] = field::byr;
	field_map["iyr"] = field::iyr;
	field_map["eyr"] = field::eyr;
	field_map["hgt"] = field::hgt;
	field_map["hcl"] = field::hcl;
	field_map["ecl"] = field::ecl;
	field_map["pid"] = field::pid;
	field_map["cid"] = field::cid;
}

std::vector<std::string> split(std::string x, char token) {
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

void day4_1() {
	std::ifstream file("input4.txt");
	int count = 0;
	std::vector<bool> fieldsPresent;
	std::vector<std::string> fields = { "byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid" };
	for (int i = 0; i < fields.size(); i++) {
		fieldsPresent.push_back(false);
	}
	for (std::string line; std::getline(file, line);) {
		if (line.empty()) {
			bool valid = true;
			for (bool b : fieldsPresent) {
				if (!b) valid = false;
			}
			count += valid;
			for (int i = 0; i < fieldsPresent.size(); i++) {
				fieldsPresent[i] = false;
			}
		}
		else {
			std::vector<std::string> keyvalues = split(line, ' ');
			for (std::string keyvalue : keyvalues) {
				std::string key = keyvalue.substr(0, 3);
				for (int i = 0; i < fields.size(); i++) {
					if (key.compare(fields[i]) == 0) fieldsPresent[i] = true;
				}
			}
		}
	}

	bool valid = true;
	for (bool b : fieldsPresent) {
		if (!b) valid = false;
	}
	count += valid;

	printf("Answer: %d\n", count);
}

void day4_2() {
	std::regex hair_color("^hcl:#[0-9a-f]{6}$");
	std::regex eye_color("^ecl:(amb|blu|brn|gry|grn|hzl|oth)$");

	initialize();
	std::ifstream file("input4.txt");
	int count = 0;
	std::vector<std::string> fields = { "byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid" };	
	std::vector<bool> fieldsValid;
	for (int i = 0; i < fields.size(); i++) {
		fieldsValid.push_back(false);
	}
	for (std::string line; std::getline(file, line);) {
		if (line.empty()) {
			bool valid = true;
			// See if all checks were correct
			for (int i = 0; i < fieldsValid.size(); i++) {
				if (!fieldsValid[i]) valid = false;
				fieldsValid[i] = false;
			}
			count += valid;
		} else {
			int value; 
			std::vector<std::string> keyvalues = split(line, ' ');
			for (std::string keyvalue : keyvalues) {
				field key = field_map[keyvalue.substr(0, 3)];
				switch (field_map[keyvalue.substr(0, 3)]) {
					case field::byr: 
						value = std::stoi(keyvalue.substr(4, keyvalue.size()));
						fieldsValid[0] = value >= 1920 && value <= 2002;
						break;
					case field::iyr:
						value = std::stoi(keyvalue.substr(4, keyvalue.size()));
						fieldsValid[1] = value >= 2010 && value <= 2020;
						break;
					case field::eyr:
						value = std::stoi(keyvalue.substr(4, keyvalue.size()));
						fieldsValid[2] = value >= 2020 && value <= 2030;
						break;
					case field::hgt: 
						if (keyvalue.substr(keyvalue.size() - 2, 2).compare("cm") == 0) {
							value = std::stoi(keyvalue.substr(4, keyvalue.size() - 6));
							fieldsValid[3] = value >= 150 && value <= 193;
						}
						else if (keyvalue.substr(keyvalue.size() - 2, 2).compare("in") == 0) {
							value = std::stoi(keyvalue.substr(4, keyvalue.size() - 6));
							fieldsValid[3] = value >= 59 && value <= 76;
						}
						else {
							fieldsValid[3] = false;
						}
						break;
					case field::hcl:
						fieldsValid[4] = keyvalue[4] == '#' && keyvalue.size() == 11 && keyvalue.find_first_not_of("0123456789abcdef", 5) == std::string::npos;
						break;
					case field::ecl:
						fieldsValid[5] = regex_match(keyvalue, eye_color);
						break;
					case field::pid:
						fieldsValid[6] = keyvalue.size() == 13;
						break;
					default:
						break;
				}
			}
		}
	}
	bool valid = true;
	for (int i = 0; i < fieldsValid.size(); i++) {
		if (!fieldsValid[i]) valid = false;
		fieldsValid[i] = false;
	}
	count += valid;

	std::cout << "Answer: " << count << std::endl;

}