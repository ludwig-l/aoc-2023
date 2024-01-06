#include <iostream>
#include <fstream>
#include <string>
#include <vector>


const std::string INPUT_FILE = "test_input.txt";
//const std::string INPUT_FILE = "puzzle_input.txt";
const char CHAR_OPERATIONAL = '#';
const char CHAR_DAMAGED = '.';
const char CHAR_UNKNOWN = '?';


int main(int argc, char** argv)
{
    std::vector<std::string> arrangements = {};
    std::ifstream text_file(INPUT_FILE);

    for (std::string line; std::getline(text_file, line);) {

        std::cout << line << '\n';

        arrangements.push_back(line);
    }

    // find the number of possible arrangements
    // ...
}