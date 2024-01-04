#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>


const std::string INPUT_FILE = "test_input.txt";
//const std::string INPUT_FILE = "puzzle_input.txt";
const char CHAR_GALAXY = '#';
const char CHAR_EMPTY_SPACE = '.';


void expand_universe(std::vector<std::string>& universe)
{
    unsigned int n_rows = universe.size();
    unsigned int n_cols = universe[0].size();

    // expand row-wise
    for (auto it = universe.begin(); it < universe.end(); it++) {
        std::string line = *it;
        if (std::find(line.begin(), line.end(), CHAR_GALAXY) == line.end()) {
            universe.insert(it, std::string(n_cols, CHAR_EMPTY_SPACE));
            n_rows++;
            it++;
        }
    }

    // expand column-wise
    // naïve approach: just go through each row for a fixed column for all columns (do kind of the same for the case of inserting the values)
    for (unsigned int col = 0; col < n_cols; col++) {
        bool found_galaxy = false;
        for (unsigned int row = 0; row < n_rows; row++) {
            if (universe[row][col] == CHAR_GALAXY) {
                found_galaxy = true;
                break;
            }
        }
        if (!found_galaxy) {
            // add one more column of empty space characters before the current one
            for (unsigned int row = 0; row < n_rows; row++) {
                universe[row].insert(col, 1, CHAR_EMPTY_SPACE);
            }
            col++;
            n_cols++;
        }
    }
}


int main(int argc, char** argv)
{
    std::vector<std::string> universe = {};
    std::ifstream text_file(INPUT_FILE);

    for (std::string line; std::getline(text_file, line);) {

        std::cout << line << '\n';

        universe.push_back(line);
    }

    expand_universe(universe);

    std::cout << "Finished\n";
}