#include <vector>
#include <array>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <stdexcept>

const std::string INPUT_FILE = "puzzle_input.txt";


void determine_part_number_positions(std::vector<int> &part_number_positions, std::string file_input, int n_rows, int n_cols, const int symbol_index)
{
    // check the eight differenet possible adjecent symbols

    // watch out for edge cases:
    // * line break character
    // * index out of scope
    // -> not necessary for the kind of input file that is given for the puzzle

    // left
    if (isdigit(file_input[symbol_index - 1])) {
        part_number_positions.push_back(symbol_index - 1);
    }

    // right
    if (isdigit(file_input[symbol_index + 1])) {
        part_number_positions.push_back(symbol_index + 1);
    }

    // up
    if (isdigit(file_input[symbol_index - n_cols - 1])) {
        part_number_positions.push_back(symbol_index - n_cols - 1);
    }

    // down
    if (isdigit(file_input[symbol_index + n_cols + 1])) {
        part_number_positions.push_back(symbol_index + n_cols + 1);
    }

    // left-up
    if (isdigit(file_input[symbol_index - n_cols - 2])) {
        part_number_positions.push_back(symbol_index - n_cols - 2);
    }

    // right-up
    if (isdigit(file_input[symbol_index - n_cols])) {
        part_number_positions.push_back(symbol_index - n_cols);
    }

    // left-down
    if (isdigit(file_input[symbol_index + n_cols])) {
        part_number_positions.push_back(symbol_index + n_cols);
    }

    // rifght-down
    if (isdigit(file_input[symbol_index + n_cols + 2])) {
        part_number_positions.push_back(symbol_index + n_cols + 2);
    }
}


void extract_part_number_from_index(std::vector<int> &part_numbers_per_symbol, const std::vector<int> part_number_positions, const std::string file_input)
{

    for (int part_number_idx : part_number_positions) {

        int start_idx = -1;
        int end_idx = -1;

        // find left-end digit
        int i = part_number_idx;
        while (true) {
            if (!isdigit(file_input[i]) || i < 0) {
                start_idx = i+1;
                break;
            }
            i--;
        }

        // find right-end digit
        i = part_number_idx;
        while (true) {
            if (!isdigit(file_input[i])) {
                end_idx = i-1;
                break;
            }
            i++;
        }

        if (start_idx == -1) {
            throw std::invalid_argument("Start index not set correctly.");
        }
        if (end_idx == -1) {
            throw std::invalid_argument("End index not set correctly.");
        }

        // get number from file input substring
        part_numbers_per_symbol.push_back(std::stoi(file_input.substr(start_idx, end_idx+1)));
    }
}


bool is_symbol(char* c)
{
    // symbol: a character that is not a digit or a "." or a linebreak character

    if (!isdigit(*c) && *c != '.' && *c != '\n') {
        return true;
    }
    else {
        return false;
    }
}


int main(int argc, char **argv)
{
    // get number of rows and columns by reading in one line
	std::ifstream text_file(INPUT_FILE);
	std::string line;

	if (!text_file.is_open()) {
		std::cout << "File " << INPUT_FILE << " could not be opened correctly.\n";
	}

    int n_rows = 0;
    int n_cols = 0;
    char text_input[n_rows][n_cols];
	if (text_file.is_open()) {
		while ( getline(text_file, line) )
		{
            if (n_cols == 0) {
                n_cols = line.length();
            }
            else if (n_cols != 0 && line.length() != n_cols && line != "") {
                std::cout << "Lines of input do not have the same length\n";
                return 1;
            }

            // if the last line is an empty one don't add it to the count
            if (line != "") {
                n_rows++;
            }
        }
	}
    text_file.close();

    // get input as character array
	std::ifstream text_file_2(INPUT_FILE);
    const char* file_input_str;
    std::string file_input;
	if (!text_file_2.is_open()) {
		std::cout << "File " << INPUT_FILE << " could not be opened correctly.\n";
	}
	if (text_file_2.is_open()) {
        file_input = std::string((std::istreambuf_iterator<char>(text_file_2)), std::istreambuf_iterator<char>());
    }
    text_file_2.close();


    std::cout << "columns: " << n_cols << "; rows: " << n_rows << "\n";

    // now let's implement a method for determining pair numbers

    std::vector<int> part_numbers = {};
    std::vector<int> part_number_positions = {};
    int index = 0;
    // go through each character in the string and check for part numbers
    for (auto it = file_input.begin(); it != file_input.end(); it++) {
        if (is_symbol(&(*it)) && *it != '\n') {
            determine_part_number_positions(part_number_positions, file_input, n_rows, n_cols, index);
            // check indices and respective full numbers by walking left and right until no digits are there anymore
            std::vector<int> part_numbers_per_symbol = {};
            extract_part_number_from_index(part_numbers_per_symbol, part_number_positions, file_input);
            // remove duplicate entries
            std::sort(part_numbers_per_symbol.begin(), part_numbers_per_symbol.end());
            part_numbers_per_symbol.erase(std::unique( part_numbers_per_symbol.begin(), part_numbers_per_symbol.end() ), part_numbers_per_symbol.end());
            // add to vector for collecting all part numbers
            part_numbers.insert(part_numbers.end(), part_numbers_per_symbol.begin(), part_numbers_per_symbol.end());
            part_number_positions.clear();
            part_numbers_per_symbol.clear();
            std::cout << "Check\n";
        }
        index++;
    }

    // sum up the list of part numbers
    int sum_of_part_numbers = std::accumulate(part_numbers.begin(), part_numbers.end(),
                                              decltype(part_numbers)::value_type(0));
    std::cout << "Sum of part numbers: " << sum_of_part_numbers << "\n";

    return 0;
}
