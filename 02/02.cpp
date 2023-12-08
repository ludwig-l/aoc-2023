#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <numeric>

// definitions
const std::string INPUT_FILE = "puzzle_input.txt";
const char SET_DELIMITER_CHARACTER = ';';
const char CUBE_DELIMITER_CHARACTER = ',';
const std::map<std::string, int> N_CUBES_AVAILABLE = {
    {"red", 12},
    {"green", 13},
    {"blue", 14}
};


int main(int argc, char** argv)
{
    // vector for storing the valid game IDs
    std::vector<int> valid_game_ids = {};

    // read in line by line collecting the ID of each possible game
    // ...
	std::ifstream text_file(INPUT_FILE);
	std::string line;

	if (!text_file.is_open()) {
		std::cout << "File " << INPUT_FILE << " could not be opened correctly.\n";
	}

	if (text_file.is_open()) {
        int game_id = 1; // just use a counter for determining the game ID
		while ( getline(text_file, line) ) {
            // extract number of cube sets with respective number of cubes

            std::string current_str;
            int n_invalid_picks = 0;

            // start traversing the line after the "Game " characters
            bool line_data_start = false;
            for (auto it = line.begin() + 5; it != line.end(); it++) {

                // don't start with the cube check before the game ID prefix did not pass
                if (line_data_start == false) {

                    // data starts after ":" and whitespace
                    if (*it == ' ') {
                        line_data_start = true;
                    }

                }
                else {

                    // start checking the amount of cubes and their color once a delimiter character is reached
                    if (*it == SET_DELIMITER_CHARACTER || *it == CUBE_DELIMITER_CHARACTER || *(it + 1) == *line.end()) {
                        // extract cube color and amount and check if this is a valid number
                        // if not valid -> continue the while loop and don't add it to the vector of valid games

                        // special case: the next character would be the end of the line
                        // just add the last remaining character already, the for loop will end immediately after this iteration anyways
                        if (*(it + 1) == *line.end()) {
                            current_str += *it;
                        }

                        // walk until whitespace character appears
                        int n_cubes = 0;
                        std::string cube_color = "";
                        for (auto it_2 = current_str.begin(); it_2 != current_str.end(); it_2++) {
                            // number of cubes
                            if (isdigit(*it_2) && *(it_2 + 1) == ' ') {
                                //n_cubes = std::stoi(current_str);
                                n_cubes = std::stoi(std::string(current_str.begin(), current_str.begin() + current_str.find(' ')));
                            }
                            // cube color
                            if (it_2 == current_str.end() - 1) {

                                // maybe check that the search result only returns one solution before continueing
                                cube_color = std::string(current_str.begin() + current_str.find(' ') + 1, current_str.end());

                                // check if game is valid
                                if (n_cubes > N_CUBES_AVAILABLE.at(cube_color)) {
                                    n_invalid_picks++;
                                }

                            }
                        }
                        // clear current string and move line iterator two characters (comma and whitespace) further
                        current_str.clear();

                        // quick and dirty solution:
                        // break the for loop when the line and is reached because after modifying the iterator the loop would continue then
                        if (*(it + 1) == *line.end()) {
                            break;
                        }

                        it += 2;
                    }

                    current_str += *it;

                }
            }
            // check if there are any invalid games in this game
            // (probably not the most efficient way to check at the end only and not breaking loops already before, but otherwise the code would be much more unreadable/complicated)
            if (n_invalid_picks == 0) {
                valid_game_ids.push_back(game_id);
            }
            game_id++;
		}
	}
    text_file.close();

    // sum up the valid game IDs in order to receive the final solution
    int sum_of_elemts = std::accumulate(valid_game_ids.begin(), valid_game_ids.end(),
                                        decltype(valid_game_ids)::value_type(0));
    std::cout << "Sum of IDs of valid games: " << sum_of_elemts << "\n";
}
