#include <vector>
#include <fstream>
#include <iostream>
#include <utility>
#include <cassert>
#include <numeric>


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


void transpose_vector_of_strings(const std::vector<std::string>& vector_of_strings, std::vector<std::string>& new_vector_of_strings)
{
    // assuming that input is empty
    assert(new_vector_of_strings.empty());

    // fill vector with empty strings
    for (unsigned int i = 0; i < vector_of_strings[0].size(); i++) {
        new_vector_of_strings.push_back("");
    }

    // insert values into new vector such that rows and columns get interchanged
    for (std::string row : vector_of_strings) {
        for (unsigned int i = 0; i < row.size(); i++) {
            new_vector_of_strings[i].push_back(row[i]);
        }
    }
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

    /* observation:
    per pattern there is exactly one reflection present, either vertical or hirizontal, but never both at once
    The reflections always have to be along the whole rows/columns except for the last or first one
    Can just take the number of rows/columns, if even -> look at the two positions around the middle and check for symmetry, if odd -> look at the two possibilities with the first/last row/column being igored for the symmetry test
    There are actually just a few possible positions for symmetry tests -> make use of that
    anyways it seems like row/column amounts are always odd numbers
    */

    std::vector<unsigned int> n_lines_above_collected = {};
    std::vector<unsigned int> n_lines_left_collected = {};
    for (std::vector<std::string> pattern : patterns) {
        unsigned int n_rows = pattern.size();
        unsigned int n_cols = pattern.front().size();
        int n_lines_above = -1;
        if (n_rows % 2 != 0) {
            // making use of integer devision here
            auto possible_symmetry_center_1 = std::make_pair(n_rows/2 - 1, n_rows/2);
            auto possible_symmetry_center_2 = std::make_pair(n_rows/2, n_rows/2 + 1);

            if (is_symmetric_pattern(pattern, possible_symmetry_center_1)) {
                n_lines_above = std::get<0>(possible_symmetry_center_1) + 1;
            }
            else if (is_symmetric_pattern(pattern, possible_symmetry_center_2)) {
                n_lines_above = std::get<0>(possible_symmetry_center_2) + 1;
            }
        }
        else {
            std::cout << "Number of rows is even. This should not happen ...\n";
            return -1;
        }
        int n_lines_left = -1;
        if (n_cols % 2 != 0) {
            // invert the rows and columns (i.e. transpose)
            std::vector<std::string> pattern_transposed = {};
            transpose_vector_of_strings(pattern, pattern_transposed);

            // use same method like before with the rows
            auto possible_symmetry_center_1 = std::make_pair(n_cols/2 - 1, n_cols/2);
            auto possible_symmetry_center_2 = std::make_pair(n_cols/2, n_cols/2 + 1);
            if (is_symmetric_pattern(pattern_transposed, possible_symmetry_center_1)) {
                n_lines_left = std::get<0>(possible_symmetry_center_1) + 1;
            }
            else if (is_symmetric_pattern(pattern_transposed, possible_symmetry_center_2)) {
                n_lines_left = std::get<0>(possible_symmetry_center_2) + 1;
            }
            std::cout << "Check\n";
        }
        else {
            std::cout << "Number of columns is even. This should not happen ...\n";
            return -1;
        }

        // add wanted line count to a data structure for collecting
        if (n_lines_above == -1 && n_lines_left == -1) {
            std::cout << "Neither vertical nor horizontal symmetry detected. This should not happen ...\n";
            return -1;
        }
        else if (n_lines_above >= 0) {
            n_lines_above_collected.push_back(n_lines_above);
        }
        else if (n_lines_left >= 0) {
            n_lines_left_collected.push_back(n_lines_left);
        }
    }

    // sum up total score according to rule
    unsigned int total_score = std::accumulate(n_lines_left_collected.begin(), n_lines_left_collected.end(), 0);
    for (unsigned int n_lines : n_lines_above_collected) {
        total_score += 100 * n_lines;
    }

    // info output
    std::cout << "Total score:\n" << total_score << '\n';
}