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

void FileType::add_file(unsigned long long int size) {
	count++;
	totalBytes += size;
};

unsigned int FileType::get_count() const {
	return count;
};

unsigned long long int FileType::get_total_bytes() const {
	return totalBytes;
}

// HELPER FUNCTIONS

// This custom comparator will be used to compare two map values
bool fileComparator(const std::pair<std::string, FileType>& a, const std::pair<std::string, FileType>& b) {
	return a.second.get_total_bytes() < b.second.get_total_bytes();
}

unsigned int calculate_length(unsigned int num) {

	unsigned int length = 0;
	while (num != 0) {
		num /= 10;
		++length;
	}

	return length;
}

unsigned int calculate_length(unsigned long long int num) {

	unsigned int length = 0;
	while (num != 0) {
		num /= 10;
		++length;
	}

	return length;
}

std::string format_int(unsigned long long int number) {

	std::string tmpStr = std::to_string(number);
	std::string newStr;

	unsigned int count = 0;
	const int thousandSeperator = 3;

	for (int i = tmpStr.size() - 1; i >= 0; i--, count++) {

		if (count % thousandSeperator == 0 && count != 0) {
			newStr.append(",");
		}

		newStr += tmpStr.at(i);

	}

	std::reverse(newStr.begin(), newStr.end());

	return newStr;

}



// Functions

// Function that will calculate how many digits in length an int is

unsigned int find_longest_filetype(FileMap& fileMap) {

	unsigned int size = 0;
	FileMap::iterator it = fileMap.begin();

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

unsigned int count_total_files(FileVec& fileVec) {

	FileVec::iterator it;

	it = fileVec.begin();

	unsigned int count = 0;

	for (; it != fileVec.end(); it++) {

		count += it->second.get_count();

	}

	return count;

}

unsigned int get_total_size(FileVec& fileVec) {

	unsigned int runningCount = 0;

	FileVec::iterator it = fileVec.begin();

	for (; it != fileVec.end(); it++) {

		runningCount += it->second.get_total_bytes();

	}

	return runningCount;

}

void get_files(std::filesystem::path path, FileMap& fileMap) {

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

void get_files(std::filesystem::path path, FileMap& fileMap, std::string regexStr) {

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


void map_to_vec(FileMap &from, std::vector<FilePair> &to) {
	
	// Got help from https://www.techiedelight.com/sort-map-values-cpp/
	// This will copy all the values from the map to a vector
	std::copy(from.begin(), from.end(),
		std::back_inserter<FileVec>(to));

}


void tempPrintVec(FileVec vec) {

	FileVec::iterator it = vec.begin();

	for (; it != vec.end(); it++) {

		std::cout << it->second.get_total_bytes() << std::endl;

	}

}


void print_files(FileVec& fileVec) {

	const unsigned int TOTAL_PADDING = 5;

	FileVec::iterator it = fileVec.begin();
	unsigned int fileTotal = 0;
	unsigned long long int totalSize = 0;

	unsigned int paddingExtension = 0;
	unsigned int paddingCount = 0;
	unsigned int paddingSize = format_int(get_total_size(fileVec)).size();

	// Iterate through fileVec and find the longest of values
	for (; it != fileVec.end(); it++) {

		unsigned int countDigitCount = calculate_length(it->second.get_count());


		if (paddingCount < countDigitCount) {
			paddingCount = countDigitCount;
		}

	}

	it = fileVec.begin();

	// Find the size of the largest extension string
	for (; it != fileVec.end(); it++) {

		if (paddingExtension < it->first.size()) {
			paddingExtension = it->first.size();
		}

	}

	paddingExtension += 1;
	paddingCount += TOTAL_PADDING;
	paddingSize += TOTAL_PADDING;

	it = fileVec.begin();

	// Print the header
	std::cout << std::setw(paddingExtension) << "Ext";
	std::cout << std::setw(paddingCount) << "#";
	std::cout << std::setw(paddingSize) << "Total";
	std::cout << std::endl << std::endl;

	// Iterate throughout the map
	for (; it != fileVec.end(); it++) {

		fileTotal += it->second.get_count();
		totalSize += it->second.get_total_bytes();

		std::cout << std::setw(paddingExtension) << it->first;
		std::cout << std::setw(paddingCount) << it->second.get_count();
		std::cout << std::setw(paddingSize) << format_int(it->second.get_total_bytes()) << std::endl;

	}

	std::cout << std::endl;
	std::cout << std::setw(paddingExtension) << fileVec.size();
	std::cout << std::setw(paddingCount) << count_total_files(fileVec);
	std::cout << std::setw(paddingSize) << format_int(get_total_size(fileVec));

}