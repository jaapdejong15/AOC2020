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

unsigned long long evaluate2(std::vector<std::string> expression, bool print=false) {
	// Replace brackets

	if (print) {
		std::cout << "EVALUATING: ";
		for (std::string x : expression) {
			std::cout << x << ' ';
		}
		std::cout << std::endl;
	}
	std::vector<std::string> withoutBrackets;
	for (int i = 0; i < expression.size(); i++) {
		if (expression[i][0] == '(') {
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
			withoutBrackets.push_back(std::to_string(evaluate2(betweenBrackets)));
			i = j;
		}
		else {
			withoutBrackets.push_back(expression[i]);
		}
	}

	if (print) {
		for (std::string x : withoutBrackets) {
			std::cout << x << ' ';
		}
		std::cout << std::endl;
	}

	// Replace + operator
	std::vector<std::string> withoutPlus;
	unsigned long long total = 0;
	for (std::string x : withoutBrackets) {
		if (x[0] == '*') {
			withoutPlus.push_back(std::to_string(total));
			withoutPlus.push_back("*");
			total = 0;
		}
		else if (x[0] != '+') {
			total += std::stoull(x);
		}
	}
	withoutPlus.push_back(std::to_string(total));

	if (print) {
		for (std::string x : withoutPlus) {
			std::cout << x << ' ';
		}
		std::cout << std::endl;
	}

	unsigned long long answer = 1;
	for (std::string x : withoutPlus) {
		if (x[0] != '*') {
			answer *= std::stoull(x);
		}
	}

	if (print) {
		printf("Answer: %llu\n", answer);
	}
	return answer;
}

unsigned long long day18_2(Timer& timer)
{
	unsigned long long answer = 0;
	std::vector<std::string> input = getStringInput("input18.txt");
	for (std::string line : input) {
		std::vector<std::string> expression = splitter(line, ' ');
		unsigned long long value = evaluate2(expression, false);
		answer += value;
	}
	return answer;
	return 0;
}
