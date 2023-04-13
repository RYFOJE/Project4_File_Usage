#pragma once
#include <filesystem>
#include <string>
#include <map>
#include <iostream>

void get_files(std::filesystem::path path, std::map<std::string, unsigned long long int>& fileMap);
void print_map(std::map<std::string, unsigned long long int>& fileMap);
