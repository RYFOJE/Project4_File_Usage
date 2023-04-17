#pragma once
#include <string>
#include <vector>
#include <filesystem>

typedef std::vector <std::string> ArgsVec;

class CMDArguments {
public:
	CMDArguments(int argc, char* argv[]);
	void printSelf();

	// All the switches
	bool isRegex = false;
	bool isHelp = false;
	bool isSortSize = false;
	bool isReversed = false;
	std::filesystem::path path;
	std::string regexString;

private:

	// Data Members
	ArgsVec argsVec;

	// Utility functions (This is private since I only want one public function that accepts all the CMD Arguments)
	ArgsVec cmd_to_vector(int argc, char* argv[]);
	bool find_help();
	bool find_regex();
	bool find_sort_size();
	bool find_reversed();
	std::string find_regex_string();
	std::filesystem::path find_file_path();
	void find_sr_rs();
};
