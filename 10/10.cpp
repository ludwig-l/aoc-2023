#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <utility>
#include <algorithm>


//const std::string INPUT_FILE = "test_input.txt";
const std::string INPUT_FILE = "puzzle_input.txt";
const char TILE_VERT = '|';
const char TILE_HOR = '-';
const char TILE_NORTH_EAST = 'L';
const char TILE_NORTH_WEST = 'J';
const char TILE_SOUTH_WEST = '7';
const char TILE_SOUTH_EAST = 'F';
const char TILE_GROUND = '.';
const char TILE_START = 'S';
const char TILE_DUMMY = '*';


std::pair<unsigned int, unsigned int> go_to_next_tile(const std::vector<std::string>& diagram, const std::pair<unsigned int, unsigned int>& last_pos, const std::pair<unsigned int, unsigned int>& cur_pos)
{
    std::pair<unsigned int, unsigned int> next_pos;

    // check what the current tile type and based on that decide for the next position

    if (diagram[std::get<0>(cur_pos)][std::get<1>(cur_pos)] == TILE_VERT) {
        if (last_pos == std::make_pair(std::get<0>(cur_pos)+1, std::get<1>(cur_pos))) {
            next_pos = std::make_pair(std::get<0>(cur_pos)-1, std::get<1>(cur_pos));
        }
        else if (last_pos == std::make_pair(std::get<0>(cur_pos)-1, std::get<1>(cur_pos))) {
            next_pos = std::make_pair(std::get<0>(cur_pos)+1, std::get<1>(cur_pos));
        }
        else {
            std::cout << "TILE_VERT: This should not happen...\n";
        }
    }

    if (diagram[std::get<0>(cur_pos)][std::get<1>(cur_pos)] == TILE_HOR) {
        if (last_pos == std::make_pair(std::get<0>(cur_pos), std::get<1>(cur_pos)+1)) {
            next_pos = std::make_pair(std::get<0>(cur_pos), std::get<1>(cur_pos)-1);
        }
        else if (last_pos == std::make_pair(std::get<0>(cur_pos), std::get<1>(cur_pos)-1)) {
            next_pos = std::make_pair(std::get<0>(cur_pos), std::get<1>(cur_pos)+1);
        }
        else {
            std::cout << "TILE_HOR: This should not happen...\n";
        }
    }

    if (diagram[std::get<0>(cur_pos)][std::get<1>(cur_pos)] == TILE_NORTH_EAST) {
        if (last_pos == std::make_pair(std::get<0>(cur_pos)-1, std::get<1>(cur_pos))) {
            next_pos = std::make_pair(std::get<0>(cur_pos), std::get<1>(cur_pos)+1);
        }
        else if (last_pos == std::make_pair(std::get<0>(cur_pos), std::get<1>(cur_pos)+1)) {
            next_pos = std::make_pair(std::get<0>(cur_pos)-1, std::get<1>(cur_pos));
        }
        else {
            std::cout << "TILE_NORTH_EAST: This should not happen...\n";
        }
    }

    if (diagram[std::get<0>(cur_pos)][std::get<1>(cur_pos)] == TILE_NORTH_WEST) {
        if (last_pos == std::make_pair(std::get<0>(cur_pos)-1, std::get<1>(cur_pos))) {
            next_pos = std::make_pair(std::get<0>(cur_pos), std::get<1>(cur_pos)-1);
        }
        else if (last_pos == std::make_pair(std::get<0>(cur_pos), std::get<1>(cur_pos)-1)) {
            next_pos = std::make_pair(std::get<0>(cur_pos)-1, std::get<1>(cur_pos));
        }
        else {
            std::cout << "TILE_NORTH_WEST: This should not happen...\n";
        }
    }

    if (diagram[std::get<0>(cur_pos)][std::get<1>(cur_pos)] == TILE_SOUTH_WEST) {
        if (last_pos == std::make_pair(std::get<0>(cur_pos)+1, std::get<1>(cur_pos))) {
            next_pos = std::make_pair(std::get<0>(cur_pos), std::get<1>(cur_pos)-1);
        }
        else if (last_pos == std::make_pair(std::get<0>(cur_pos), std::get<1>(cur_pos)-1)) {
            next_pos = std::make_pair(std::get<0>(cur_pos)+1, std::get<1>(cur_pos));
        }
        else {
            std::cout << "TILE_SOUTH_WEST: This should not happen...\n";
        }
    }

    if (diagram[std::get<0>(cur_pos)][std::get<1>(cur_pos)] == TILE_SOUTH_EAST) {
        if (last_pos == std::make_pair(std::get<0>(cur_pos), std::get<1>(cur_pos)+1)) {
            next_pos = std::make_pair(std::get<0>(cur_pos)+1, std::get<1>(cur_pos));
        }
        else if (last_pos == std::make_pair(std::get<0>(cur_pos)+1, std::get<1>(cur_pos))) {
            next_pos = std::make_pair(std::get<0>(cur_pos), std::get<1>(cur_pos)+1);
        }
        else {
            std::cout << "TILE_SOUTH_EAST: This should not happen...\n";
        }
    }

    return next_pos;
}


int main(int argc, char** argv)
{
    /*
    idea:
    *   search for start position and safe the location
    *   look for the two connections starting from the start position
    *   use a function that, given the coordinate where it connected from, find the direction
        where it connects to (there is always only one possible direction)
    *   do this pipe maze discovery for both directions from the starting point on and count
        the the number of steps
    *   stop when the two paths meet at the same position
    *   return the numer of steps it took from the starting points to the point that is the
        furthest away from the starting point regarding both possible paths
    */

    std::vector<std::string> diagram = {};
    std::ifstream text_file(INPUT_FILE);

    for (std::string line; std::getline(text_file, line);) {

        std::cout << line << '\n';

        diagram.push_back(line);
    }
    std::cout << "Check\n";

    // search for the two possible directions at the beginning
    // need to find the starting point in the whole map at first (there should be only one starting point in the whole map)
    int start_pos_row = 0;
    int start_pos_col = 0;
    for (; start_pos_row < diagram[0].size(); start_pos_row++) {
        auto res = std::find(diagram[start_pos_row].begin(), diagram[start_pos_row].end(), TILE_START);
        if (res != diagram[start_pos_row].end()) {
            //start_pos_col = *res;
            start_pos_col = res - diagram[start_pos_row].begin();
            break;
        }
    }

    // now search for the two directions where there are connections
    std::vector<std::pair<int, int>> possible_directions = {};
    char symbol = TILE_DUMMY;

    // north
    if (start_pos_row - 1 >= 0) {
        std::pair<int, int> pos_north = std::make_pair(start_pos_row - 1, start_pos_col);
        symbol = diagram[std::get<0>(pos_north)][std::get<1>(pos_north)];
        if (symbol == TILE_VERT || symbol == TILE_SOUTH_WEST || symbol == TILE_SOUTH_EAST) {
            possible_directions.push_back(pos_north);
        }
    }

    // east
    if (start_pos_col + 1 <= diagram[start_pos_col].size()) {
        std::pair<int, int> pos_east = std::make_pair(start_pos_row, start_pos_col + 1);
        symbol = diagram[std::get<0>(pos_east)][std::get<1>(pos_east)];
        if (symbol == TILE_HOR || symbol == TILE_NORTH_WEST || symbol == TILE_SOUTH_WEST)
        {
            possible_directions.push_back(pos_east);
        }
    }

    // south
    if (start_pos_row + 1 <= diagram.size()) {
        std::pair<int, int> pos_south = std::make_pair(start_pos_row + 1, start_pos_col);
        symbol = diagram[std::get<0>(pos_south)][std::get<1>(pos_south)];
        if (symbol == TILE_VERT || symbol == TILE_NORTH_EAST || symbol == TILE_NORTH_WEST) {
            possible_directions.push_back(pos_south);
        }
    }

    // west
    if (start_pos_col - 1 >= 0) {
        std::pair<int, int> pos_west = std::make_pair(start_pos_row, start_pos_col - 1);
        symbol = diagram[std::get<0>(pos_west)][std::get<1>(pos_west)];
        if (symbol == TILE_HOR || symbol == TILE_NORTH_EAST || symbol == TILE_NORTH_WEST) {
            possible_directions.push_back(pos_west);
        }
    }

    if (possible_directions.size() != 2) {
        std::cout << "Number of possible directions should be 2, is " << possible_directions.size() << '\n';
    }

    std::cout << "Finished\n";
}