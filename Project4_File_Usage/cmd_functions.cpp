#include <regex>
#include <filesystem>
#include <iostream>

#include "cmd_functions.h"

bool is_valid_path(std::string str) {

	std::filesystem::path path(str);

	return std::filesystem::exists(path);
}

// Create function definitions for CMD Functions
CMDArguments::CMDArguments(int argc, char* argv[]) {
	argsVec = cmd_to_vector(argc, argv);

	isHelp = find_help();
	isRegex = find_regex();
	isSortSize = find_sort_size();
	isReversed = find_reversed();

	// If the user wants to only use regex, this will be called upon to find the regex string
	if (isRegex) {
		regexString = find_regex_string();
	}

	path = find_file_path();
	find_sr_rs();

}

ArgsVec CMDArguments::cmd_to_vector(int argc, char* argv[]) {

	ArgsVec args;

	// Add all the strings to the args vector
	for (int i = 0; i < argc; i++) {
		args.push_back(argv[i]);
	}

	return args;
}

bool CMDArguments::find_regex() {

	ArgsVec::iterator it = std::find(argsVec.begin(), argsVec.end(), "-x");

	// Return if the user has used a switch -x
	return it != argsVec.end();

}

bool CMDArguments::find_help() {

	ArgsVec::iterator it = std::find(argsVec.begin(), argsVec.end(), "-h");

	if (it != argsVec.end()) {
		return true;
	}

	it = std::find(argsVec.begin(), argsVec.end(), "--help");

	return it != argsVec.end();

}

bool CMDArguments::find_sort_size() {

	ArgsVec::iterator it = std::find(argsVec.begin(), argsVec.end(), "-s");

	return it != argsVec.end();

}

bool CMDArguments::find_reversed() {

	ArgsVec::iterator it = std::find(argsVec.begin(), argsVec.end(), "-r");

	return it != argsVec.end();

}

std::string CMDArguments::find_regex_string() {

	ArgsVec::iterator it = std::find(argsVec.begin(), argsVec.end(), "-x");

	// Get the value beside the -x switch
	it++;

	if (it == argsVec.end()) {
		return "";
	}

	// Return the neighbor string to the -x switch
	return *it;
}

std::filesystem::path CMDArguments::find_file_path() {

	// Try to find a valid file path
	ArgsVec::iterator it = std::find_if(argsVec.begin() + 1, argsVec.end(), is_valid_path);

	// If no argument is found, use the running directory
	if (it == argsVec.end()) {
		return std::filesystem::current_path();
	}

	return std::filesystem::path(*it);

}

void CMDArguments::find_sr_rs() {

	// I know this is bad code, but I do not ahve the time to properly implement the search for switches
	// I'm sorry

	ArgsVec::iterator it = std::find(argsVec.begin() + 1, argsVec.end(), "-rs");

	if (it != argsVec.end()) {
		isSortSize = true;
		isReversed = true;
		return;
	}

	it = std::find(argsVec.begin() + 1, argsVec.end(), "-sr");

	if (it != argsVec.end()) {
		isSortSize = true;
		isReversed = true;
		return;
	}
}

void CMDArguments::printSelf() {

	std::cout << "is regex: " << isRegex << std::endl;
	std::cout << "is help: " << isHelp << std::endl;
	std::cout << "is sort size: " << isSortSize << std::endl;
	std::cout << "is reversed: " << isReversed << std::endl;
	std::cout << "path to check: " << path.string() << std::endl;
	std::cout << "regex string: " << regexString << std::endl << std::endl;

}
