#include "day19.h"
#include <unordered_map>

bool match(std::string message, std::unordered_map<int, std::vector<std::string>>& rules, std::unordered_map<int, int>& rule_lengths, int ruleNr = 0) {
	if (rule_lengths[ruleNr] != message.size()) return false;
	if (rules[ruleNr][0][0] == '\"') return message[0] == rules[ruleNr][0][1];
	int messagePointer = 0;
	bool correct = true;
	bool second_part = false;
	int nxtRule;
	int size;
	for (std::string x : rules[ruleNr]) {
		if (x[0] == '|') {
			if (correct) break;
			correct = true;
			second_part = true;
			messagePointer = 0;
		}
		else {
			nxtRule = std::stoi(x);
			size = rule_lengths[nxtRule];
			if (!match(message.substr(messagePointer, size), rules, rule_lengths, nxtRule)) {
				correct = false;
				if (second_part) break;
			}
			messagePointer += size;
		}
	}
	return correct && messagePointer == message.size();
}

bool match2(std::string message, std::unordered_map<int, std::vector<std::string>>& rules, std::unordered_map<int, int>& rule_lengths, int ruleNr = 0) {
	int length42 = rule_lengths[42];
	int length31 = rule_lengths[31];
	if (ruleNr == 0) {
		for (int i = 1; i < message.size() - 1; i++) {
			if (i % length42 == 0 && (message.size() - i) % (length42 + length31) == 0 && match2(message.substr(i), rules, rule_lengths, 11) && match2(message.substr(0, i), rules, rule_lengths, 8)) return true;
		}
		return false;
	}
	else if (ruleNr == 8) {
		int messagePointer = 0;
		while (messagePointer < message.size()) {
			if (!match(message.substr(messagePointer, length42), rules, rule_lengths, 42)) {
				return false;
			}
			messagePointer += length42;
		}
		return true;
	} 
	else if (ruleNr == 11) {
		int lowerPointer = 0;
		int upperPointer = message.size();
		while (lowerPointer < upperPointer) {
			lowerPointer += length42;
			upperPointer -= length31;
			if (!match(message.substr(lowerPointer - length42, length42), rules, rule_lengths, 42) || !match(message.substr(upperPointer, length31), rules, rule_lengths, 31)) {
				return false;
			}
		}
		return true;
	}
}

void find_rule_lengths(std::unordered_map<int, std::vector<std::string>>& rules, std::unordered_map<int, int> &rule_lengths, int rule=0) {
	if (rules[rule][0][0] == '\"') {
		rule_lengths[rule] = 1;
		return;
	}
	std::vector<int> ruleNrs;
	for (std::string x : rules[rule]) {
		if (x.size() != 0 && x[0] != '|') {
			int ruleNr = std::stoi(x);
			if (rule_lengths.find(ruleNr) == rule_lengths.end()) find_rule_lengths(rules, rule_lengths, ruleNr);
			ruleNrs.push_back(ruleNr);
		}
		else ruleNrs.clear();
	}
	int total_length = 0;
	for (int ruleNr : ruleNrs) total_length += rule_lengths[ruleNr];
	rule_lengths[rule] = total_length;
}

unsigned long long day19_1(Timer& timer)
{
	std::vector<std::string> input = getStringInput("input19.txt");

	timer.start();
	std::unordered_map<int, std::vector<std::string>> rules;
	std::unordered_map<int, int> rule_lengths;
	int i = 0;
	while (input[i].size() != 0) {
		std::string line = input[i];
		if (line.size() == 0) break;
		int ruleNr = std::stoi(line.substr(0, line.find(':')));
		std::string rule = line.substr(line.find(':') + 2);
		rules[ruleNr] = splitter(rule, ' ');
		i++;
	}
	find_rule_lengths(rules, rule_lengths);
	int count = 0;
	i++;
	for (; i < input.size(); i++) {
		if (match(input[i], rules, rule_lengths, 0)) {
			count++;
		}
	}
	timer.stop();
	return count;
}

unsigned long long day19_2(Timer& timer)
{
	std::vector<std::string> input = getStringInput("input19.txt");

	timer.start();
	std::unordered_map<int, std::vector<std::string>> rules;
	std::unordered_map<int, int> rule_lengths;
	int i = 0;
	while (input[i].size() != 0) {
		std::string line = input[i];
		if (line.size() == 0) break;
		int ruleNr = std::stoi(line.substr(0, line.find(':')));
		std::string rule = line.substr(line.find(':') + 2);
		rules[ruleNr] = splitter(rule, ' ');
		i++;
	}

	find_rule_lengths(rules, rule_lengths);
	int count = 0;
	i++;
	for (; i < input.size(); i++) {
		if (match2(input[i], rules, rule_lengths, 0)) {
			count++;
		}
	}
	timer.stop();
	return count;
}
