#include "day16.h"
#include <unordered_set>
#include <set>
#include <utility>

int day16_1(Timer& timer)
{
	std::vector<std::string> input = getStringInput("input16.txt");
	
	std::unordered_set<int> validNumbers;

	timer.start();
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

	timer.stop();
	return errorRate;
}

long long day16_2(Timer& timer)
{
	std::vector<std::string> input = getStringInput("input16.txt");

	std::vector<std::pair<int, int>> validRanges;
	std::vector<std::string> fields;
	std::unordered_set<int> validNumbers;

	timer.start();

	// Read the rules
	int i;
	for (i = 0; ; i++) {
		std::string s = input[i];
		if (s.size() == 0) break;
		std::vector<std::string> split = splitter(s, ' ');
		std::vector<std::string> range2 = splitter(split[split.size() - 1], '-');
		std::vector<std::string> range1 = splitter(split[split.size() - 3], '-');
		fields.push_back((split.size() == 5 ? split[0] : "") + split[split.size() - 4]);
		validRanges.push_back(std::make_pair(std::stoi(range1[0]), std::stoi(range1[1])));
		validRanges.push_back(std::make_pair(std::stoi(range2[0]), std::stoi(range2[1])));
		for (int j = std::stoi(range2[0]); j <= std::stoi(range2[1]); j++) {
			validNumbers.insert(j);
		}
		for (int j = std::stoi(range1[0]); j <= std::stoi(range1[1]); j++) {
			validNumbers.insert(j);
		}
	}
	i += 2;

	// Read my ticket
	std::vector<std::string> myValues = splitter(input[i], ',');
	i += 3;

	// Readnearby tickets
	int errorRate = 0;
	std::vector<std::vector<int>> validTickets(fields.size());
	for (; i < input.size(); i++) {
		std::string ticket = input[i];
		std::vector<std::string> strValues = splitter(ticket, ',');
		bool valid = true;
		for (std::string x : strValues) {
			if (validNumbers.find(std::stoi(x)) == validNumbers.end()) {
				valid = false;
			}
		}
		if (valid) {
			for (int j = 0; j < strValues.size(); j++) {
				validTickets[j].push_back(std::stoi(strValues[j]));
			}
		}
	}

	
	// check which field belongs where
	std::vector<std::unordered_set<int>> possibleFields(fields.size()); // Stores the possible fields for each index
	std::pair<int, int> range1;
	std::pair<int, int> range2;
	bool valid;
	for (int j = 0; j < validTickets.size(); j++) {
		for (size_t k = 0; k < fields.size(); k++) {
			range1 = validRanges[k * 2];
			range2 = validRanges[k * 2 + 1];
			valid = true;
			for (int x : validTickets[j]) {
				if (!((x >= range1.first && x <= range1.second) || (x >= range2.first && x <= range2.second))) {
					valid = false;
					break;
				}
			}
			if (valid) {
				possibleFields[j].insert(k);
			}
		}
	}

	std::unordered_set<int> fieldsFound;
	bool done;
	int field;
	while (true) {
		done = true;
		// Find a field with only one possibility
		for (std::unordered_set<int> fields : possibleFields) {
			if (fields.size() == 1 && fieldsFound.find(*fields.begin()) == fieldsFound.end()) {
				field = *fields.begin();
				done = false;
				break;
			}
		}
		if (done) break;
		// Delete the possibility from all other fields
		for (int i = 0; i < fields.size(); i++) {
			if (possibleFields[i].size() != 1) {
				possibleFields[i].erase(field);
			}
		}
		fieldsFound.insert(field);
	}

	unsigned long long answer = 1;
	for (int j = 0; j < fields.size(); j++) {
		for (int k : possibleFields[j]) {
			if (fields[k].substr(0, 9).compare("departure") == 0) {
				answer *= std::stoi(myValues[j]);
			}
		}
	}
	timer.stop();
	return answer;
}
