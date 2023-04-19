///
///	Author:		Ryan Jennings (r_jennings118029@fanshaweonline.ca)
/// 
/// Purpose:	This file contains all the functions to parse cmd arguments
/// 
/// Date:		2023-04-18 (Added documentation)
/// 


#include <regex>
#include <filesystem>
#include <iostream>

#include "cmd_functions.h"

/// <summary>
/// This will find if the str is a valid path
/// </summary>
/// <param name="str">The string to be converted to a filepath</param>
/// <returns>If the path is valid or not</returns>
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



/// <summary>
/// 
/// </summary>
/// <param name="argc"></param>
/// <param name="argv"></param>
/// <returns></returns>
ArgsVec CMDArguments::cmd_to_vector(int argc, char* argv[]) {

	ArgsVec args;

	// Add all the strings to the args vector
	for (int i = 0; i < argc; i++) {
		args.push_back(argv[i]);
	}

	return args;
}


/// <summary>
/// This will find if the user has called the -x switch, if they have, it will return true, otherwise it will return false
/// </summary>
/// <returns>A boolean value representing if the user has called -x</returns>
bool CMDArguments::find_regex() {

	ArgsVec::iterator it = std::find(argsVec.begin(), argsVec.end(), "-x");

	// Return if the user has used a switch -x
	return it != argsVec.end();

}


/// <summary>
/// This will find if the user has called the -h switch or --help, if they have, it will return true, otherwise it will return false
/// </summary>
/// <returns>A boolean value representing if the user has called -h or --help</returns>
bool CMDArguments::find_help() {

	ArgsVec::iterator it = std::find(argsVec.begin(), argsVec.end(), "-h");

	if (it != argsVec.end()) {
		return true;
	}

	it = std::find(argsVec.begin(), argsVec.end(), "--help");

	return it != argsVec.end();

}


/// <summary>
/// This will find if the user has called the -s switch, if they have, it will return true, otherwise it will return false
/// </summary>
/// <returns>A boolean value representing if the user has called -s</returns>
bool CMDArguments::find_sort_size() {

	ArgsVec::iterator it = std::find(argsVec.begin(), argsVec.end(), "-s");

	return it != argsVec.end();

}


/// <summary>
/// This will find if the user has called the -r switch, if they have, it will return true, otherwise it will return false
/// </summary>
/// <returns>A boolean value representing if the user has called -r</returns>
bool CMDArguments::find_reversed() {

	ArgsVec::iterator it = std::find(argsVec.begin(), argsVec.end(), "-r");

	return it != argsVec.end();

}


/// <summary>
/// This will find the regex string that the user has entered, it works by iterating through all the arguments until the -x
/// switch is found. Then it will return the next argument, which should be the regex string if none is found, it will return an empty string
/// 
/// A better implementation should throw an error if the user has not entered a regex string
/// </summary>
/// <returns>A string corresponding to the regex to search</returns>
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


/// <summary>
/// This function will find the file path that the user has entered, it works by iterating through all the arguments until a valid path is found
/// if none is found, it will return the path to the CWD
/// </summary>
/// <returns>A path representing where the program will calculate the file extension size</returns>
std::filesystem::path CMDArguments::find_file_path() {

	// Try to find a valid file path
	ArgsVec::iterator it = std::find_if(argsVec.begin() + 1, argsVec.end(), is_valid_path);

	// If no argument is found, use the running directory
	if (it == argsVec.end()) {
		return std::filesystem::current_path();
	}

	return std::filesystem::path(*it);

}


/// <summary>
/// This function will check to see if the user has used the -sr or -rs switches
/// this is a bad implementation, but I do not have the time to properly implement this
/// 
/// sorry
/// </summary>
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
