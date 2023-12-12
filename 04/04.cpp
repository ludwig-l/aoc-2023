#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <cmath>
#include <algorithm>

const std::string INPUT_FILE = "puzzle_input.txt";

int main(int argc, char **argv)
{
    int points_total = {};

	std::ifstream text_file(INPUT_FILE);
	std::string line;

	if (!text_file.is_open()) {
		std::cout << "File " << INPUT_FILE << " could not be opened correctly.\n";
	}

    // read in line by line
	if (text_file.is_open()) {
		while ( getline(text_file, line) )
		{
            std::vector<int> winning_numbers;
            std::vector<int> own_numbers;
            std::string current_number_str = "";
            
            bool is_winning_numbers_substr = false;
            bool is_own_numbers_substr = false;
            // walk until a colon character is found
            for (std::string::iterator it = line.begin(); it <= line.end(); it++) {

                // winning numbers substring
                if (is_winning_numbers_substr) {
                    if (isdigit(*it)) {
                        current_number_str.push_back(*it);
                    }
                    else if (*it == ' ') {
                        // do nothing if there is an empty string but the current string is still empty
                        if (current_number_str.empty()) {
                            ;
                        }
                        else {
                            winning_numbers.push_back(std::stoi(current_number_str));
                            current_number_str.clear();
                        }
                    }
                    else if (*it == '|') {
                        is_winning_numbers_substr = false;
                        is_own_numbers_substr = true;
                        it += 2; // next character is an empty space and loop will continue directly afterwards
                    }
                }

                // own numbers substring
                if (is_own_numbers_substr) {
                    if (isdigit(*it)) {
                        current_number_str.push_back(*it);
                    }
                    else if (*it == ' ') {
                        // do nothing if there is an empty string but the current string is still empty
                        if (current_number_str.empty()) {
                            ;
                        }
                        else {
                            own_numbers.push_back(std::stoi(current_number_str));
                            current_number_str.clear();
                        }
                    }
                    else if (it == line.end()) {
                        own_numbers.push_back(std::stoi(current_number_str));
                        current_number_str.clear();
                    }
                }

                // card number prefix
                if (!is_winning_numbers_substr && !is_own_numbers_substr) {
                    if (*it == ':') {
                        is_winning_numbers_substr = true;
                        it++; // next character is an empty space
                    }
                }
            }
            // calculate number of points by checking if a number is present in the winning numbers for each own number
            int n_winning_numbers = 0;
            for (int number : own_numbers) {
                if (std::find(winning_numbers.begin(), winning_numbers.end(), number) != winning_numbers.end()) {
                    n_winning_numbers++;
                }
            }
            int n_points = 0;
            if (n_winning_numbers != 0) {
                n_points = pow(2, n_winning_numbers - 1);
            }

            std::cout << "Winning numbers: ";
            for (int number : winning_numbers) {
                std::cout << number << " ";
            }
            std::cout << " | Own numbers: ";
            for (int number : own_numbers) {
                std::cout << number << " ";
            }
            std::cout << " ---> Points: " << n_points;
            std::cout << '\n';
            std::cout << "-----\n";

            points_total += n_points;
        }

        std::cout << "--> Total points: " << points_total << '\n';

	}
    text_file.close();
}