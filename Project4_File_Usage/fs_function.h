#pragma once
#include <filesystem>
#include <string>
#include <map>
#include <iostream>

class FileType {
	public:
		FileType();

		void add_file(unsigned long long int size);
		unsigned int get_count() const;
		unsigned long long int get_total_bytes() const;

	private:
		unsigned int count;
		unsigned long long int totalBytes;

};

typedef std::map<std::string, FileType> FileMap;
typedef std::pair<std::string, FileType> FilePair;
typedef std::vector<FilePair> FileVec;

void get_files(std::filesystem::path path, FileMap& fileMap);
void print_map(FileMap& fileMap);
void get_files(std::filesystem::path path, FileMap& fileMap, std::string regexStr);
void map_to_vec(FileMap& from, std::vector<FilePair>& to);
void tempPrintVec(FileVec vec);
