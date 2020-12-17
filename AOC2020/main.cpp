#include "timer.h"
#include <stdexcept>
#include <tuple>
#include "day1.h"
#include "day2.h"
#include "day3.h"
#include "day4.h"
#include "day5.h"
#include "day6.h"
#include "day7.h"
#include "day8.h"
#include "day9.h"
#include "day10.h"
#include "day11.h"
#include "day12.h"
#include "day13.h"
#include "day14.h"
#include "day15.h"
#include "day16.h"
#include "day17.h"

typedef int Solution(Timer& timer);
typedef long long LSolution(Timer& timer);
typedef unsigned long long ULLSolution(Timer& timer);

void run(Solution s, unsigned int times = 1) {
	if (times < 1) throw std::invalid_argument("Times should be greater than zero!");
	Timer* timer = new Timer();
	int answer;
	for (uint_fast32_t i = 0; i < times; i++) {
		answer = s(*timer);
	}
	std::tuple<double, int> timing_data = timer->getTimingData();
	printf("Answer: %d\n", answer);
	printf("\n--------===TIMER===--------\n -median time: %f ms\n -sample size: %d\n", std::get<0>(timing_data), std::get<1>(timing_data));
	delete timer;
}

void run(LSolution s, unsigned int times = 1) {
	if (times < 1) throw std::invalid_argument("Times should be greater than zero!");
	Timer* timer = new Timer();
	std::int_fast64_t answer;
	for (uint_fast32_t i = 0; i < times; i++) {
		answer = s(*timer);
	}
	std::tuple<double, int> timing_data = timer->getTimingData();
	printf("Answer: %lld\n", answer);
	printf("\n--------===TIMER===--------\n -median time: %f ms\n -sample size: %d\n", std::get<0>(timing_data), std::get<1>(timing_data));
	delete timer;
}


void run(ULLSolution s, unsigned int times = 1) {
	if (times < 1) throw std::invalid_argument("Times should be greater than zero!");
	Timer* timer = new Timer();
	std::uint_fast64_t answer;
	for (uint_fast32_t i = 0; i < times; i++) {
		answer = s(*timer);
	}
	std::tuple<double, int> timing_data = timer->getTimingData();
	printf("Answer: %llu\n", answer);
	printf("\n--------===TIMER===--------\n -median time: %f ms\n -sample size: %d\n", std::get<0>(timing_data), std::get<1>(timing_data));
	delete timer;
}

int main(){
	run(day17_2);
}