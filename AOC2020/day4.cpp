#include "day4.h"
#include <numeric>
#include <map>
#include <sstream>
#include <iterator>

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
	for (std::string entry; std::getline(file, entry);) {
		if (entry.empty()) {
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
			std::vector<std::string> keyvalues = split(entry, ' ');
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