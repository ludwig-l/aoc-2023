#include <vector>
#include <string>
#include <iostream>
#include <fstream>


const std::string INPUT_FILE = "puzzle_input.txt";


const char CHAR_ROUND_ROCK = 'O';
const char CHAR_CUBE_ROCK = '#';
const char CHAR_EMPTY_SPACE = '.';


int main(int argc, char** argv)
{
    // read in file and check for file existance first
    std::ifstream text_file(INPUT_FILE);
    if (!text_file.good()) {
        std::cout << "Given text file \"" << INPUT_FILE << "\" does not exist.\n";
        return -1;
    }

    // read in line by line and add the patterns to a vector
    std::vector<std::string> platform = {};
    for (std::string line; std::getline(text_file, line);) {

        platform.push_back(line);

    }

    std::cout << "Check\n";

    // go through line by line (from top to bottom) and move each 'O' up if there is no other 'O' or '#' in the way
    for (unsigned int row = 1; row < platform.size(); row++) {
        for (unsigned int col = 0; col < platform.front().size(); col++) {
            if (platform[row][col] == CHAR_ROUND_ROCK) {
                for (unsigned int i = row - 1; i >= 0; i--) {
                    if (platform[i][col] == CHAR_EMPTY_SPACE) {
                        platform[i][col] = CHAR_ROUND_ROCK;
                        platform[i+1][col] = CHAR_EMPTY_SPACE;
                    }
                    else {
                        break;
                    }
                    // prevent accessing elements at index -1 that would come in the next iteration
                    if (i == 0) {
                        break;
                    }
                }
            }
        }
    }

    // calculte the load
    unsigned int load = 0;
    unsigned int load_multiplier = 1;
    for (int row = platform.size() - 1; row >= 0; row--) {
        for (auto it = platform[row].begin(); it <= platform[row].end(); it++) {
            if (*it == CHAR_ROUND_ROCK) {
                load += load_multiplier;
            }
        }
        load_multiplier++;
    }

    // info output
    std::cout << "Total load: " << load << '\n';
}
