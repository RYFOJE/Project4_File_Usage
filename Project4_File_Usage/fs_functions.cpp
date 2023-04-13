#include <filesystem>
#include <string>
#include <map>
#include <iostream>
#include "fs_function.h"
#include <regex>

namespace fs = std::filesystem;
int minimumPadding = 4;

// CLASS DECLARATIONS

FileType::FileType() : count(0), totalBytes(0) {}



// Functions

// Function that will calculate how many digits in length an int is
unsigned int calculate_int_length(unsigned int num) {

	unsigned int length = 0;
	while (num != 0) {
		num /= 10;
		++length;
	}

	return length;
}

unsigned int find_longest_filetype(std::map<std::string, FileType>& fileMap ) {

	unsigned int size = 0;
	std::map<std::string, FileType>::iterator it = fileMap.begin();

	// Iterate throughout the map containing all filetypes
	for (; it != fileMap.end(); it++) {

		unsigned int currSize = it->first.length();

		if (currSize > size) {
			size = currSize;
		}

	}
	// Return the largest found size
	return size;
}




void FileType::add_file(unsigned long long int size) {
	count++;
	totalBytes += size;
};

unsigned int FileType::get_count() const {
	return count;
};

unsigned long long int FileType::get_total_bytes() const{
	return totalBytes;
}

void print_map(std::map<std::string, FileType>& fileMap) {


	std::map<std::string, FileType>::iterator it = fileMap.begin();
	unsigned int fileTotal = 0;
	unsigned long long int totalSize = 0;

	// Iterate throughout the map
	for (; it != fileMap.end(); it++) {

		fileTotal += it->second.get_count();
		totalSize += it->second.get_total_bytes();

		std::cout << std::setw()

	}

}

void get_files(std::filesystem::path path, std::map<std::string, FileType>& fileMap) {

	fs::recursive_directory_iterator dirIterator(path);
	unsigned int runningCount = 0;

	// Iterate through the directory and all its subdirectories
	for (const fs::directory_entry& dir_entry : dirIterator) {

		fs::path fp(dir_entry);

		if (fs::is_directory(fp)) {
			continue;
		}
		runningCount++;

		fileMap[fp.extension().string()].add_file( fs::file_size(fp) );
	}
}

void get_files(std::filesystem::path path, std::map<std::string, FileType>& fileMap, std::string regexStr) {

	fs::recursive_directory_iterator dirIterator(path);
	unsigned int runningCount = 0;

	// Iterate through the directory and all its subdirectories
	for (const fs::directory_entry& dir_entry : dirIterator) {

		fs::path fp(dir_entry);

		if (fs::is_directory(fp)) {
			continue;
		}

		std::regex re(regexStr);

		// if the file does not match regex
		if (!std::regex_match(fp.extension().string(), re)) {
			continue;
		}

		runningCount++;

		fileMap[fp.extension().string()].add_file(fs::file_size(fp));
	}
}
