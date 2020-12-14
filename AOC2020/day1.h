#pragma once

#include <fstream>
#include <iostream>
#include <chrono>
#include <vector>
#include <string>
#include "timer.h"
#include "helper.h"

void swap(int* a, int* b);
void quickSort(std::vector<int>& input, int l, int r);
bool logfinder(std::vector<int>& input, int num_to_find, int l, int r);

int day1_1(Timer &timer);
int day1_2(Timer &timer);
