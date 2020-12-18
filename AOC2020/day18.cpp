#include "day18.h"
#include <algorithm>

unsigned long long evaluate(std::vector<std::string> expression) {
	// Find last 
	unsigned long long answer = 0;
	char nextOperator = '+';
	unsigned long long value = 0;
	bool calculate = false;
	for (int i = 0; i < expression.size(); i++) {
		// Operators
		if (expression[i][0] == '*') {
			calculate = false;
			nextOperator = '*';
		}
		else if (expression[i][0] == '+') {
			calculate = false;
			nextOperator = '+';
		}
		// Brackets
		else if (expression[i][0] == '(') {
			calculate = true;
			std::string firstValue = expression[i].substr(1);
			int j;
			int depth = std::count(expression[i].begin(), expression[i].end(), '(');
			for (j = i + 1; j < expression.size(); j++) {
				depth -= std::count(expression[j].begin(), expression[j].end(), ')');
				depth += std::count(expression[j].begin(), expression[j].end(), '(');
				if (depth == 0) break;
			}
			std::string lastValue = expression[j].substr(0, expression[j].size() - 1);
			std::vector<std::string> betweenBrackets;
			betweenBrackets.push_back(firstValue);
			for (int k = i + 1; k < j; k++) {
				betweenBrackets.push_back(expression[k]);
			}
			betweenBrackets.push_back(lastValue);
			value = evaluate(betweenBrackets);
			i = j;
		}
		// Number
		else {
			calculate = true;
			value = std::stoull(expression[i]);
		}
		
		
		// Perform calculation
		if (calculate) {
			switch (nextOperator) {
			case '+':
				answer += value;
				break;
			case '*':
				answer *= value;
				break;
			}
		}
	}
	return answer;
}

long long day18_1(Timer& timer)
{
	unsigned long long answer = 0;
	std::vector<std::string> input = getStringInput("input18.txt");
	for (std::string line : input) {
		std::vector<std::string> expression = splitter(line, ' ');
		unsigned long long value = evaluate(expression);
		answer += value;
	}
	return answer;
}

int day18_2(Timer& timer)
{
	return 0;
}
