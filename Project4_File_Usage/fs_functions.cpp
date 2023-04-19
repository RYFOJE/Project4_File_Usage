///
/// Author:		Ryan Jennings
/// 
/// Purpose:	This file contains all the functions that are used to calculate the file usage of a given directory
///				and its subdirectories. This file also contains the FileType class which is used to store the
///				information about a given file type.
/// 
/// Date:		2023-04-18 (Added documentation)
/// 

#include <filesystem>
#include <string>
#include <map>
#include <iostream>
#include "fs_function.h"
#include <regex>

namespace fs = std::filesystem;
int minimumPadding = 4;

// CLASS DECLARATIONS


/// <summary>
/// The default constructor for the FileType class
/// </summary>
FileType::FileType() : count(0), totalBytes(0) {}


/// <summary>
/// This will add a file to the current file type
/// </summary>
/// <param name="size"></param>
void FileType::add_file(unsigned long long int size) {
	count++;
	totalBytes += size;
};


/// <summary>
/// This will return the total amount of files associated to the FileType
/// </summary>
/// <returns>Total amount of files</returns>
unsigned int FileType::get_count() const {
	return count;
};


/// <summary>
/// This will return the total amount of bytes associated to the FileType
/// </summary>
/// <returns>Total amount of bytes</returns>
unsigned long long int FileType::get_total_bytes() const {
	return totalBytes;
}

// HELPER FUNCTIONS

// This custom comparator will be used to compare two map values


/// <summary>
/// This custom comparator is used to see what file is larger than the other
/// </summary>
/// <param name="a">Left side</param>
/// <param name="b">Right Side</param>
/// <returns>True if larger, flase if not</returns>
bool fileComparator(const std::pair<std::string, FileType>& a, const std::pair<std::string, FileType>& b) {
	return a.second.get_total_bytes() < b.second.get_total_bytes();
}


/// <summary>
/// This function will accept an integer and calculate the length of a number.
/// </summary>
/// <param name="num">The integer to be calculated</param>
/// <returns>The total numbers in an integer</returns>
unsigned int calculate_length(unsigned int num) {

	unsigned int length = 0;
	while (num != 0) {
		num /= 10;
		++length;
	}

	return length;
}


/// <summary>
/// This function will accept an integer and calculate the length of a number.
/// </summary>
/// <param name="num">The integer to be calculated</param>
/// <returns>The total numbers in an integer</returns>
unsigned int calculate_length(unsigned long long int num) {

	unsigned int length = 0;
	while (num != 0) {
		num /= 10;
		++length;
	}

	return length;
}


/// <summary>
/// This will format an int with a thousands seperator.
/// </summary>
/// <param name="number">The integer to be formatted</param>
/// <returns>The formatted integer as a string</returns>
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


/// <summary>
/// This will find the longest string length of a filetype in a given FileMap
/// </summary>
/// <param name="fileMap">The filemap that will be searched</param>
/// <returns>The total count of characters of the longest extension</returns>
unsigned int find_longest_filetype(FileMap& fileMap) {

	unsigned int size = 0;
	FileMap::iterator it = fileMap.begin();

	// Iterate throughout the map containing all filetypes
	for (; it != fileMap.end(); it++) {

		size_t currSize = it->first.length();

		if (currSize > size) {
			size = currSize;
		}

	}
	// Return the largest found size
	return size;
}

/// <summary>
/// This function will sum the total count of all the files in a given FileVec.
/// </summary>
/// <param name="fileVec">The fileVec that will be counted</param>
/// <returns>the total count of files</returns>
unsigned int count_total_files(FileVec& fileVec) {

	FileVec::iterator it;

	it = fileVec.begin();

	unsigned int count = 0;

	for (; it != fileVec.end(); it++) {

		count += it->second.get_count();

	}

	return count;

}

/// <summary>
/// This function will sum the total values of all the files in a FileVec.
/// </summary>
/// <param name="fileVec">The file vector that will be calculated</param>
/// <returns>The total size of all the files in the fileVec</returns>
unsigned long long int get_total_size(FileVec& fileVec) {

	unsigned long long int runningCount = 0;

	FileVec::iterator it = fileVec.begin();

	for (; it != fileVec.end(); it++) {

		runningCount += it->second.get_total_bytes();

	}

	return runningCount;

}

/// <summary>
/// This get_file function will add files that are in the given path recusively
/// </summary>
/// <param name="path">The file path used to find all recursive files</param>
/// <param name="fileMap">The filemap used to store the information pertaining to the files</param>
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

/// <summary>
/// This get_file function will take in a regex string and will only add files that match the regex to the map
/// from the given path recursively
/// </summary>
/// <param name="path">The file path used to find all recursive files</param>
/// <param name="fileMap">The filemap used to store the information pertaining to the files</param>
/// <param name="regexStr">The regex match string used to test if the files are valid</param>
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

/// <summary>
/// Function that will copy all the values from the map to a vector as pairs
/// </summary>
/// <param name="from">The Map that will be use as the source</param>
/// <param name="to">The Vector that will hold all File Pairs</param>
void map_to_vec(FileMap &from, std::vector<FilePair> &to) {
	
	// Got help from https://www.techiedelight.com/sort-map-values-cpp/
	// This will copy all the values from the map to a vector
	std::copy(from.begin(), from.end(),
		std::back_inserter<FileVec>(to));

}

/// <summary>
/// 
/// </summary>
/// <param name="vec"></param>
void sort_files(FileVec &vec) {

	std::sort(vec.begin(), vec.end(), fileComparator);

}

/// <summary>
/// Prints out all the files in the vector in the order that they have been added to the vector
/// </summary>
/// <param name="fileVec">A vector containing pairs of file extensions and File classes that represents all the information
/// associated to the file type</param>
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