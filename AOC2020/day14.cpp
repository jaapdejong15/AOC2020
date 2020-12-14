#include "day14.h"
#include <bitset>
#include <unordered_map>

unsigned long long getMaskedValue(std::string mask, std::bitset<36> value) {
	std::string rmask = mask;
	reverse(rmask.begin(), rmask.end());
	std::bitset<36> result(0);
	for (int i = 0; i < 36; i++) {
		switch (rmask[i]) {
		case 'X':
			result[i] = value[i];
			break;
		case '0':
			result[i] = 0;
			break;
		case '1':
			result[i] = 1;
			break;
		}
	}
	return result.to_ullong();
}

long long day14_1(Timer& timer)
{
	std::unordered_map<unsigned long, unsigned long long> mem;
	std::vector<std::string> input = getStringInput("input14.txt");
	std::string mask;
	for (std::string line : input) {
		if (line[1] == 'a') {
			mask = line.substr(7);
		}
		else {
			unsigned long position = std::stoul(line.substr(4, line.find(']') - 4));
			std::bitset<36> value(std::stoi(line.substr(line.find('=') + 2)));
			mem[position] = getMaskedValue(mask, value);
		}
	}

	long long sum = 0;
	for (auto const& x : mem) {
		sum += x.second;
	}
	return sum;
}

std::vector<unsigned long long> getLocations(unsigned long long location, std::string locationMask) {
	for (int i = 0; i < 36; i++) {
		if (locationMask[35 - i] == '1') {
			location |= 1ULL << i;
		}
		else if (locationMask[35 - i] == 'X') {
			location &= ~(1ULL << i); // Set all Xs to 0.
		}
	}

	std::vector<unsigned long long> locations;
	locations.push_back(location);

	for (int i = 0; i < 36; i++) {
		if (locationMask[35 - i] == 'X') {
			int locationSize = locations.size();
			for (int j = 0; j < locationSize; j++) {
				locations.push_back(locations[j] | 1ULL << i);
			}
		}
	}
	return locations;
}

long long day14_2(Timer& timer)
{
	std::unordered_map<unsigned long long, unsigned long long> mem;
	std::vector<std::string> input = getStringInput("input14.txt");
	std::string mask;
	for (std::string line : input) {
		if (line[1] == 'a') {
			mask = line.substr(7);
		}
		else {
			unsigned long long location = std::stoull(line.substr(4, line.find(']') - 4));
			unsigned long long value = std::stoull(line.substr(line.find('=') + 2));

			std::vector<unsigned long long> locations = getLocations(location, mask);
			for (unsigned long long loc : locations) {
				mem[loc] = value;
			}
		}
	}

	long long sum = 0;
	for (auto const& x : mem) {
		sum += x.second;
	}
	return sum;
	return 0;
}
