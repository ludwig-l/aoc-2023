#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <cmath>
#include <numeric>


//const std::string INPUT_FILE = "test_input.txt";
const std::string INPUT_FILE = "puzzle_input.txt";
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

    /*
    next part thoughts:
    *   assign a number to each galaxy (assigned in raster-scan order) and a row/column coordinate pair
    *   for each galaxy pair: find the shortest path connecting the two galaxies

    */
   unsigned int n_rows = universe.size();
   unsigned int n_cols = universe[0].size(); // all row entries have the same length
   std::vector<std::pair<unsigned int, unsigned int>> galaxy_locations = {};
   for (unsigned int row = 0; row < n_rows; row++) {
       for (unsigned int col = 0; col < n_cols; col++) {
           if (universe[row][col] == CHAR_GALAXY) {
                galaxy_locations.push_back(std::make_pair(row, col));
           }
       }
   }

   std::vector<std::pair<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>>> galaxy_pairs = {};
   unsigned int count_1 = 0;
   for (auto galaxy_1 : galaxy_locations) {
       unsigned int count_2 = 0;
       for (auto galaxy_2 : galaxy_locations) {
           if ( // avoid adding duplicate pair entries by these checks
               (galaxy_1 != galaxy_2) &&
               (std::find(galaxy_pairs.begin(), galaxy_pairs.end(), std::make_pair(galaxy_1, galaxy_2)) == galaxy_pairs.end()) &&
               (std::find(galaxy_pairs.begin(), galaxy_pairs.end(), std::make_pair(galaxy_2, galaxy_1)) == galaxy_pairs.end())) {
               galaxy_pairs.push_back(std::make_pair(galaxy_1, galaxy_2));
           }
           std::cout << count_1 << " / " << galaxy_locations.size() << " | " << count_2 << " / " << galaxy_locations.size() << '\n';
           count_2++;
       }
       count_1++;
   }

   // calculate shortest lengths
   std::vector<unsigned int> shortest_path_lengths = {};
   for (auto pairs : galaxy_pairs)
   {
       shortest_path_lengths.push_back(
           abs(std::get<0>(std::get<0>(pairs)) - std::get<0>(std::get<1>(pairs))) + abs(std::get<1>(std::get<0>(pairs)) - std::get<1>(std::get<1>(pairs))));
   }
   int sum_of_shortest_paths = std::accumulate(shortest_path_lengths.begin(), shortest_path_lengths.end(),
                                               decltype(shortest_path_lengths)::value_type(0));

   std::cout << "The sum of shortest paths is: " << sum_of_shortest_paths << '\n';
}