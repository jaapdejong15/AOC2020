#include "day1.h"

void swap(int* a, int* b) {
	int c = *a;
	*a = *b;
	*b = c;
}

void quickSort(std::vector<int>& input, int l, int r) {
	if (l < r) {
		int pivot = input[(r + l) / 2];
		int i = l, j = r;
		while (i <= j) {
			while (input[i] < pivot) {
				i++;
			}
			while (input[j] > pivot) {
				j--;
			}
			if (i <= j) {
				swap(&input[i], &input[j]);
				i++;
				j--;
			}
		}

		quickSort(input, l, i - 1);
		quickSort(input, i, r);
	}
}

bool logfinder(std::vector<int>& input, int num_to_find, int l, int r) {
	if (l >= r) {
		return input[l] == num_to_find;
	}
	int m = (r + l) / 2;
	if (input[m] == num_to_find) {
		return true;
	}
	else if (input[m] < num_to_find) return logfinder(input, num_to_find, m + 1, r);
	else return logfinder(input, num_to_find, l, m - 1);
}

int day1_1(Timer &timer) {
	std::vector<int> input = getIntInput("input1.txt");

	timer.start();
	quickSort(input, 0, input.size() - 1);

	int answer = 0;

	for (int i = 0; i < input.size(); i++) {
		int num_to_find = 2020 - input[i];
		if (logfinder(input, num_to_find, 0, input.size() - 1)) {
			answer = num_to_find * input[i];
			break;
		}
	}

	timer.stop();
	return answer;
}

int day1_2(Timer &timer) {
	std::vector<int> input = getIntInput("input1.txt");

	timer.start();
	quickSort(input, 0, input.size() - 1);

	int answer = 0;

	for (int i = 0; i < input.size(); i++) {
		int sum_to_find = 2020 - input[i];
		for (int j = 0; j < input.size(); j++) {
			if (input[i] + input[j] > sum_to_find) {
				break;
			}
			else {
				int num_to_find = sum_to_find - input[j];
				if (logfinder(input, num_to_find, 0, input.size() - 1)) {
					answer = input[i] * input[j] * num_to_find;
					break;
				}
			}
		}
	}

	timer.stop();
	return answer;
}