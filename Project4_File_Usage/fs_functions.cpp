#include <filesystem>
#include <string>
#include <map>
#include <iostream>

namespace fs = std::filesystem;

void print_map(std::map<std::string, unsigned long long int>& fileMap) {

	std::map<std::string, unsigned long long int>::iterator it = fileMap.begin();

	// Iterate throughout the map
	for (; it != fileMap.end(); it++) {

		std::cout << it->first << " : "
			<< it->second << std::endl;

	}

}


void get_files(std::filesystem::path path, std::map<std::string, unsigned long long int>& fileMap) {

	fs::recursive_directory_iterator dirIterator(path);
	unsigned int runningCount = 0;

	// Iterate through the directory and all its subdirectories
	for (const fs::directory_entry& dir_entry : dirIterator) {

		fs::path fp(dir_entry);

		if (fs::is_directory(fp)) {
			continue;
		}
		runningCount++;

		fileMap[fp.extension().string()] += fs::file_size(fp);

		// std::cout << fp.extension() << " ---- " << fp.filename() << std::endl;

	}

}
