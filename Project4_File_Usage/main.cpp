///
/// Project 4 File Usage
/// 
/// Author:		Ryan Jennings
/// 
/// Purpose:	This program will take a directory and find the file usage of all the files in the directory and its subdirectories.
/// 
/// Date:		2023-04-18 (Added documentation)
/// 

#include <filesystem>
#include <string>
#include <map>
#include "fs_function.h"
#include "cmd_functions.h"
#include "general_functions.h"

int main(int argc, char* argv[]) {

	CMDArguments args(argc, argv);
	
	if (args.isHelp) {
		print_help();
		return EXIT_SUCCESS;
	}

	std::filesystem::path path(args.path);
	std::map<std::string, FileType> fileMap;

	// Search with regex
	if (args.isRegex) {
		get_files(path, fileMap, args.regexString);
	}

	// Search without regex
	else {
		get_files(path, fileMap);
	}

	// Convert from map to vector so it is easy to sort and manipulate
	FileVec fileVec;
	map_to_vec(fileMap, fileVec);

	if (args.isSortSize) {
		sort_files(fileVec);
	}

	if (args.isReversed) {
		std::reverse(fileVec.begin(), fileVec.end());
	}

	print_files(fileVec);
	
}