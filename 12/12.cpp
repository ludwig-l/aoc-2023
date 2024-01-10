#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "spring_arrangement.h"


//const std::string INPUT_FILE = "test_input.txt";
const std::string INPUT_FILE = "puzzle_input.txt";


int main(int argc, char** argv)
{
    std::vector<SpringArrangement> arrangements = {};
    std::ifstream text_file(INPUT_FILE);

    for (std::string line; std::getline(text_file, line);) {

        // separate values by white space
        std::istringstream string_stream(line);
        std::string springs = "";
        std::vector<unsigned int> group_sizes = {};
        for (std::string element; std::getline(string_stream, element, ' ');) {

            if (springs == "") {
                springs = element;
            }
            else if (group_sizes.empty()) {
                // split by commas characters and append them to a vector, then save to variable
                std::istringstream string_stream_2(element);
                for (std::string str; std::getline(string_stream_2, str, ',');) {
                    group_sizes.push_back(std::stoi(str));
                }
            }
        }
        arrangements.push_back(SpringArrangement(springs, group_sizes));
        std::cout << line << " -> " << arrangements.back().get_n_possible_arrangement_combinations() << " possible arrangemnts\n";
    }

    // find the number of possible arrangements
    unsigned int n_all_possible_spring_arrangements = 0;
    for (SpringArrangement arrangement : arrangements) {
        n_all_possible_spring_arrangements += arrangement.get_n_possible_arrangement_combinations();
    }
    std::cout << "-> Total number of all possible spring arrangements: " << n_all_possible_spring_arrangements << '\n';
}