#include <vector>
#include <fstream>
#include <iostream>
//#include <sstream>
#include <utility>


const std::string INPUT_FILE = "test_input.txt";
const char CHAR_ASH = '.';
const char CHAR_ROCK = '#';


bool is_symmetric_pattern(std::vector<std::string>& pattern, std::pair<unsigned int, unsigned int>& symmetry_center)
{
    /// test if there is a symmetry between the rows of the pattern, as soon as the symmetry is detected wrong false is returned
    for (unsigned int i = 0; i < pattern.size()/2; i++) {
        if (pattern[std::get<0>(symmetry_center)-i] != pattern[std::get<1>(symmetry_center)+i]) {
            return false;
        }
    }
    return true;
}


int main(int argc, char** argv)
{

    // read in line by line and add the patterns to a vector
    std::vector<std::vector<std::string>> patterns = {};
    std::ifstream text_file(INPUT_FILE);
    std::vector<std::string> current_pattern = {};
    for (std::string line; std::getline(text_file, line);) {

        if (line == "") {
            patterns.push_back(current_pattern);
            current_pattern.clear();
        }
        else {
            current_pattern.push_back(line);
        }

    }
    patterns.push_back(current_pattern); // add last entry to patterns

    std::cout << "Check\n";

    /* observation:
    per pattern there is exactly one reflection present, either vertical or hirizontal, but never both at once
    The reflections always have to be along the whole rows/columns except for the last or first one
    Can just take the number of rows/columns, if even -> look at the two positions around the middle and check for symmetry, if odd -> look at the two possibilities with the first/last row/column being igored for the symmetry test
    There are actually just a few possible positions for symmetry tests -> make use of that
    anyways it seems like row/column amounts are always odd numbers
    */
    for (std::vector<std::string> pattern : patterns) {
        unsigned int n_rows = pattern.size();
        unsigned int n_cols = pattern.front().size();
        std::vector<std::pair<unsigned int, unsigned int>> possible_symmetry_centers;
        unsigned int lines_above = 0;
        if (n_rows % 2 != 0) {
            // making use of integer devision here
            auto possible_symmetry_center_1 = std::make_pair(n_rows/2 - 1, n_rows/2);
            auto possible_symmetry_center_2 = std::make_pair(n_rows/2, n_rows/2 + 1);

            if (is_symmetric_pattern(pattern, possible_symmetry_center_1)) {
                lines_above = std::get<0>(possible_symmetry_center_1) + 1;
            }
            else if (is_symmetric_pattern(pattern, possible_symmetry_center_2)) {
                lines_above = std::get<0>(possible_symmetry_center_2) + 1;
            }
            else {
                // this pattern does not have vertical symmetry
                // ..
                ;
            }
            
        }
        else {
            std::cout << "This should not happen ...\n";
            return -1;
        }
        if (n_cols % 2 != 0) {
            // for the columns the rows and columns can be exchanged and then the same code as for the vertical symmetry can be used
            // ...
            ;
        }
    }
}