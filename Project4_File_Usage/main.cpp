#include <filesystem>
#include <string>
#include <map>
#include "fs_function.h"

int main() {

	std::string s = "C:\\School\\2023W\\INFO-1156-04\\Projects\\Project4_File_Usage\\Project4_File_Usage\\Temp";

	std::filesystem::path path(s);

	std::map<std::string, unsigned long long int> fileMap;

	get_files(path, fileMap);
	print_map(fileMap);

}