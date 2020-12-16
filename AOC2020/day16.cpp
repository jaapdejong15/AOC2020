#include "day16.h"
#include <unordered_set>

int day16_1(Timer& timer)
{
	std::vector<std::string> input = getStringInput("input16.txt");
	
	std::unordered_set<int> validNumbers;

	//rules
	int i;
	for (i = 0; ; i++) {
		std::string s = input[i];
		if (s.size() == 0) break;
		std::vector<std::string> split = splitter(s, ' ');
		std::vector<std::string> range2 = splitter(split[split.size() - 1], '-');
		std::vector<std::string> range1 = splitter(split[split.size() - 3], '-');
		//std::string field = (split.size() == 5 ? split[0] : "") + split[split.size() - 4];
		for (int j = std::stoi(range2[0]); j <= std::stoi(range2[1]); j++) {
			validNumbers.insert(j);
		}
		for (int j = std::stoi(range1[0]); j <= std::stoi(range1[1]); j++) {
			validNumbers.insert(j);
		}
	}
	i += 5;

	//nearby tickets
	int errorRate = 0;
	for (; i < input.size(); i++) {
		std::string ticket = input[i];
		std::vector<std::string> strValues = splitter(ticket, ',');
		for (std::string x : strValues) {
			if (validNumbers.find(std::stoi(x)) == validNumbers.end()) {
				errorRate += std::stoi(x);
			}
		}
	}


	return errorRate;
}

int day16_2(Timer& timer)
{
	return 0;
}
