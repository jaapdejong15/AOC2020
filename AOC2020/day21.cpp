#include "day21.h"
#include <sstream>
#include <set>

#include <algorithm>
#include <iterator>
#include <map>

int day21_1(Timer& timer)
{
	std::vector<std::string> input = getStringInput("input21.txt");
	std::vector<std::set<std::string>> ingredients(input.size());
	std::vector<std::set<std::string>> allergens(input.size());

	std::set<std::string> allergen_types;
	std::set<std::string> ingredient_types;

	timer.start();

	for (int i = 0; i < input.size(); i++) {
		std::istringstream line(input[i]);
		std::string word;
		bool ingredient = true;
		while (line >> word) {
			if (word.compare("(contains") == 0) {
				ingredient = false;
			}
			else if (ingredient) {
				ingredients[i].insert(word);
				ingredient_types.insert(word);
			}
			else {
				allergens[i].insert(word.substr(0, word.size() - 1));
				allergen_types.insert(word.substr(0, word.size() - 1));
			}
		}
	}

	std::map<std::string, std::set<std::string>> ingredient_possibilities;
	
	for (std::string allergen : allergen_types) {
		std::set<std::string> possible_ingredients = ingredient_types;
		for (int i = 0; i < input.size(); i++) {
			if (allergens[i].find(allergen) != allergens[i].end()) {
				std::set<std::string> intersect;
				std::set_intersection(possible_ingredients.begin(), possible_ingredients.end(), ingredients[i].begin(), ingredients[i].end(), std::inserter(intersect, intersect.begin()));
				possible_ingredients = intersect;
			}
		}
		ingredient_possibilities[allergen] = possible_ingredients;
	}

	std::set<std::string> important_ingredients;
	std::map<std::string, std::string> associated_ingredients;
	while (true) {
		std::string ingredient_to_remove = "";
		for (std::string allergen : allergen_types) {
			std::set<std::string> possibilities = ingredient_possibilities[allergen];
			if (possibilities.size() == 1) {
				ingredient_to_remove = *possibilities.begin();
				associated_ingredients[allergen] = ingredient_to_remove;
				important_ingredients.insert(ingredient_to_remove);
				break;
			}
		}
		if (ingredient_to_remove.size() == 0) break;
		for (std::string allergen : allergen_types) {
			ingredient_possibilities[allergen].erase(ingredient_to_remove);
		}
	}

	for (std::string ingredient : important_ingredients) {
		ingredient_types.erase(ingredient);
	}

	int answer = 0;
	for (std::set<std::string> x : ingredients) {
		for (std::string ingredient : ingredient_types) {
			answer += x.find(ingredient) != x.end();
		}
	}

	timer.stop();

	return answer;
}

std::string day21_2(Timer& timer)
{
	std::vector<std::string> input = getStringInput("input21.txt");
	std::vector<std::set<std::string>> ingredients(input.size());
	std::vector<std::set<std::string>> allergens(input.size());

	std::set<std::string> allergen_types;
	std::set<std::string> ingredient_types;

	timer.start();

	for (int i = 0; i < input.size(); i++) {
		std::istringstream line(input[i]);
		std::string word;
		bool ingredient = true;
		while (line >> word) {
			if (word.compare("(contains") == 0) {
				ingredient = false;
			}
			else if (ingredient) {
				ingredients[i].insert(word);
				ingredient_types.insert(word);
			}
			else {
				allergens[i].insert(word.substr(0, word.size() - 1));
				allergen_types.insert(word.substr(0, word.size() - 1));
			}
		}
	}

	std::map<std::string, std::set<std::string>> ingredient_possibilities;

	for (std::string allergen : allergen_types) {
		std::set<std::string> possible_ingredients = ingredient_types;
		for (int i = 0; i < input.size(); i++) {
			if (allergens[i].find(allergen) != allergens[i].end()) {
				std::set<std::string> intersect;
				std::set_intersection(possible_ingredients.begin(), possible_ingredients.end(), ingredients[i].begin(), ingredients[i].end(), std::inserter(intersect, intersect.begin()));
				possible_ingredients = intersect;
			}
		}
		ingredient_possibilities[allergen] = possible_ingredients;
	}

	std::set<std::string> important_ingredients;
	std::map<std::string, std::string> associated_ingredients;
	while (true) {
		std::string ingredient_to_remove = "";
		for (std::string allergen : allergen_types) {
			std::set<std::string> possibilities = ingredient_possibilities[allergen];
			if (possibilities.size() == 1) {
				ingredient_to_remove = *possibilities.begin();
				associated_ingredients[allergen] = ingredient_to_remove;
				important_ingredients.insert(ingredient_to_remove);
				break;
			}
		}
		if (ingredient_to_remove.size() == 0) break;
		for (std::string allergen : allergen_types) {
			ingredient_possibilities[allergen].erase(ingredient_to_remove);
		}
	}

	std::string answer = "";
	
	for (std::pair<std::string, std::string> entry : associated_ingredients) {
		answer += entry.second;
		answer.push_back(',');
	}
	answer = answer.substr(0, answer.size() - 1);

	timer.stop();

	return answer;
}
