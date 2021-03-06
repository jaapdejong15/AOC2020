#pragma once

#include <fstream>
#include <iostream>
#include <chrono>
#include <vector>
#include <string>

std::vector<uint64_t> getInt64Input(std::string filename);

std::vector<int> getIntInput(std::string filename);

std::vector<std::string> getStringInput(std::string filename);

std::vector<std::string> splitter(std::string x, char token);