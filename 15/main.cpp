#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <numeric>
#include "../file_utils.h"


const char CHAR_SEPARATOR = ',';


unsigned int compute_hash_value(std::string& str)
{
    unsigned int current_value = 0;

    for (char c : str) {
        current_value += (c);
        current_value *= 17;
        current_value = current_value % 256;
    }

    return current_value;
}


int main(int argc, char** argv)
{
    if (FileUtils::get_file_status(argc, argv) != FileUtils::InputFileStatus::ok) {
        return -1;
    }
    std::fstream text_file(argv[1]);

    // read in line by line and add the patterns to a vector
    // (there should only be one line in this puzzle's input)
    std::vector<std::string> initialization_sequence = {};
    for (std::string line; std::getline(text_file, line);) {

        std::istringstream str_stream(line);
        for (std::string val; std::getline(str_stream, val, CHAR_SEPARATOR);) {
            initialization_sequence.push_back(val);
        }
    }

    std::vector<unsigned int> results = {};
    for (std::string step : initialization_sequence) {
        unsigned int result = compute_hash_value(step);
        results.push_back(result);
    }
    unsigned int sum_of_reslts = std::accumulate(results.begin(), results.end(), 0);
    std::cout << "-> Sum of results: " << sum_of_reslts << '\n';
}