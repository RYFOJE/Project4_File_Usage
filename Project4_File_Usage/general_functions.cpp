#include <iostream>

/// <summary>
/// This will print out the help context to the user
/// </summary>
void print_help() {

    std::cout << "fileusage {v3.0.0} (c) 2023 - 23, Ryan Jennings" << std::endl;
    std::cout << std::endl;
    std::cout << "\tUsage: fileusage [--help] [-hrs(x regularexpression)] [folder]" << std::endl;
    std::cout << "\tswitches:" << std::endl;
    std::cout << "\t\th       help" << std::endl;
    std::cout << "\t\tr       reverse the order of the listing" << std::endl;
    std::cout << "\t\ts       sort by file sizes" << std::endl;
    std::cout << "\t\tx       filter with a regular expression" << std::endl;
    std::cout << std::endl;
    std::cout << "\tfolder" << std::endl;
    std::cout << "\t\tstarting folder or current folder if not provided" << std::endl;
}