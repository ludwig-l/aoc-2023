#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <numeric>


const std::string INPUT_FILE = "puzzle_input.txt";


bool is_all_zeros(std::vector<int> numbers)
{
    bool all_zeros = true;
    for (int number : numbers) {
        if (number != 0) {
            all_zeros == false;
            return false;
        }
    }
    return all_zeros;
}


int main(int argc, char **argv)
{
    std::vector<std::vector<int>> histories;

    // read in file line by line and then element by element
    std::ifstream text_file(INPUT_FILE);

    for (std::string line; std::getline(text_file, line);) {

        std::cout << line << '\n';

        std::vector<int> current_history = {};
        std::istringstream string_stream(line);
        for (std::string element; std::getline(string_stream, element, ' ');) {
            current_history.push_back(std::stoi(element));
        }
        histories.push_back(current_history);
    }

    std::cout << "Finished reading in data.\n";

    std::vector<unsigned int> numbers = {};
    

    // go through the different histories and calculate the respective values
    for (std::vector<int> history : histories) {

        std::vector<std::vector<int>> differences = {};
        std::vector<int> current_diferences = {};
        std::vector<int> current_numbers = history;

        // create a new vector of difference until the differences are all zeros
        while (true)
        {
            for (unsigned int i = 0; i < current_numbers.size() - 1; i++) {
                current_diferences.push_back(current_numbers[i+1] - current_numbers[i]);
            }
            differences.push_back(current_diferences);
            current_numbers = current_diferences;
            if (std::all_of(current_diferences.begin(), current_diferences.end(), [](int i) { return i == 0; })) {
                break;
            }
            current_diferences = {};
        }


        differences.insert(differences.begin(), history);
        differences[differences.size()-1].push_back(0);
        // go from last added difference to newest one
        for (unsigned int i = differences.size()-1; i > 0; i--) {
            differences[i-1].push_back(*(differences[i].end()-1) + *(differences[i-1].end()-1));
        }

        // save number of interest
        numbers.push_back(*(differences[0].end()-1));

    }

    // calculate the final number by adding up all individual numbers
    unsigned int final_number = std::accumulate(numbers.begin(), numbers.end(), decltype(numbers)::value_type(0));

    // print result info
    std::cout << "The final number is: " << final_number << '\n';
}