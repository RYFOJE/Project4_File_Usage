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

void get_files(std::filesystem::path path, std::map<std::string, FileType>& fileMap);
void print_map(std::map<std::string, FileType>& fileMap);
