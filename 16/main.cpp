#include <vector>
#include <string>
#include <utility>
#include <cassert>
#include <algorithm>
#include <memory>
#include "../file_utils.h"


const char CHAR_EMPTY_SPACE = '.';
const char CHAR_MIRROR_SLASH = '/';
const char CHAR_MIRROR_BACKSLASH = '\\';
const char CHAR_SPLITTER_VERT = '|';
const char CHAR_SPLITTER_HOR = '-';
const char CHAR_ENERGIZED = '#';
const std::pair<int, int> POS_START = std::make_pair(0, 0);

enum class Direction {
    north = 0,
    east,
    south,
    west
};

const Direction DIRECTION_START = Direction::east;

struct Movement {
    std::pair<int, int> position;
    Direction direction;
    Movement() : position(std::make_pair(0, 0)), direction(Direction::north) {;} // default constructor
    Movement(const std::pair<int, int>& position, const Direction& direction) : position(position), direction(direction) {;}
    bool operator==(const Movement& m) const
    {
        if ((position == m.position) && (direction == m.direction)) {
            return true;
        }
        else {
            return false;
        }
    }
};

template <typename T>
bool is_inside_bounds(const std::pair<int, int>& position, const T& field)
{
    // check if the given position is inside the field

    // compute number of rows and columns
    unsigned int n_rows = field.size();
    unsigned int n_cols = field.front().size(); // can assume same size for each column

    if ((std::get<0>(position) < 0) || (std::get<1>(position) < 0) || (std::get<0>(position) >= n_rows) || (std::get<1>(position) >= n_cols)) {
        return false;
    }
    else {
        return true;
    }
}

std::unique_ptr<std::vector<Direction>> determine_next_movement_directions(const Direction previous_direction, const char object)
{
    // given the current character and the previous movement direction determine the next movement direction(s)

    std::unique_ptr<std::vector<Direction>> next_movement_directions(new std::vector<Direction>());

    assert(next_movement_directions->empty()); // expecting an empty vector for saving the results to

    if (object == CHAR_EMPTY_SPACE) {
        next_movement_directions->push_back(previous_direction);
    }
    else if (object == CHAR_SPLITTER_HOR) {
        if (previous_direction == Direction::east || previous_direction == Direction::west) {
            next_movement_directions->push_back(previous_direction);
        }
        else if (previous_direction == Direction::north || previous_direction == Direction::south) {
            next_movement_directions->push_back(Direction::east);
            next_movement_directions->push_back(Direction::west);
        }
        else {
            std::cerr << "No valid character detected.\n";
        }
    }
    else if (object == CHAR_SPLITTER_VERT) {
        if (previous_direction == Direction::north || previous_direction == Direction::south) {
            next_movement_directions->push_back(previous_direction);
        }
        else if (previous_direction == Direction::east || previous_direction == Direction::west) {
            next_movement_directions->push_back(Direction::north);
            next_movement_directions->push_back(Direction::south);
        }
        else {
            std::cerr << "No valid character detected.\n";
        }
    }
    else if (object == CHAR_MIRROR_SLASH) {
        if (previous_direction == Direction::north) {
            next_movement_directions->push_back(Direction::east);
        }
        else if (previous_direction == Direction::east) {
            next_movement_directions->push_back(Direction::north);
        }
        else if (previous_direction == Direction::south) {
            next_movement_directions->push_back(Direction::west);
        }
        else if (previous_direction == Direction::west) {
            next_movement_directions->push_back(Direction::south);
        }
        else {
            std::cerr << "No valid character detected.\n";
        }
    }
    else if (object == CHAR_MIRROR_BACKSLASH) {
        if (previous_direction == Direction::north) {
            next_movement_directions->push_back(Direction::west);
        }
        else if (previous_direction == Direction::east) {
            next_movement_directions->push_back(Direction::south);
        }
        else if (previous_direction == Direction::south) {
            next_movement_directions->push_back(Direction::east);
        }
        else if (previous_direction == Direction::west) {
            next_movement_directions->push_back(Direction::north);
        }
        else {
            std::cerr << "No valid character detected.\n";
        }
    }
    else {
        std::cerr << "No valid character detected.\n";
    }

    assert(next_movement_directions->size() <= 2);

    return next_movement_directions;
}


int main(int argc, char** argv)
{
    if (FileUtils::get_file_status(argc, argv) != FileUtils::InputFileStatus::ok) {
        return -1;
    }
    std::fstream text_file(argv[1]);

    // read in file
    std::vector<std::string> contraption = {};
    for (std::string line; std::getline(text_file, line);) {

        contraption.push_back(line);

    }

    // construct field of empty space characters for later counting of the energized tiles
    std::string row_of_empty_spaces(contraption.front().size(), CHAR_EMPTY_SPACE);
    std::vector<std::string> energized_tiles(contraption.size(), row_of_empty_spaces);

    // construct first movement object
    std::vector<Direction> first_movement_directions = *determine_next_movement_directions(DIRECTION_START, contraption[std::get<0>(POS_START)][std::get<1>(POS_START)]);
    std::vector<Movement> start_movements = {};
    for (Direction direction : first_movement_directions) {
        Movement movement(POS_START, direction);
        start_movements.push_back(movement);
    }

    std::vector<Movement> movements_to_process = start_movements;
    std::vector<Movement> already_processed_movements = {};
    // go through the movements to process as long as there are any (new ones might be added during the program run)
    while (movements_to_process.size() > 0) {

        // current movement that is being evaluated will be removed from the "stack"
        Movement current_movement = movements_to_process.back();
        already_processed_movements.push_back(current_movement);
        movements_to_process.pop_back();

        // energize current tile
        energized_tiles[std::get<0>(current_movement.position)][std::get<1>(current_movement.position)] = CHAR_ENERGIZED;

        std::pair<int, int> new_position;
        if (current_movement.direction == Direction::north) {
            new_position = std::make_pair(std::get<0>(current_movement.position) - 1, std::get<1>(current_movement.position));
        }
        else if (current_movement.direction == Direction::east) {
            new_position = std::make_pair(std::get<0>(current_movement.position), std::get<1>(current_movement.position) + 1);
        }
        else if (current_movement.direction == Direction::south) {
            new_position = std::make_pair(std::get<0>(current_movement.position) + 1, std::get<1>(current_movement.position));
        }
        else if (current_movement.direction == Direction::west) {
            new_position = std::make_pair(std::get<0>(current_movement.position), std::get<1>(current_movement.position) - 1);
        }
        else {
            std::cerr << "Error.\n";
            return -1;
        }

        if (is_inside_bounds(new_position, contraption)) {

            std::vector<Direction> next_movement_directions = *determine_next_movement_directions(current_movement.direction, contraption[std::get<0>(new_position)][std::get<1>(new_position)]);

            // put all available next steps (there should be either one or two) to the object storing the movements to still process
            for (Direction direction : next_movement_directions) {
                Movement movement(new_position, direction);
                // add next movement to movements to process list only if they did not appear already
                if (std::find(already_processed_movements.begin(), already_processed_movements.end(), movement) == already_processed_movements.end())
                    {
                        movements_to_process.push_back(movement);
                    }
            }
        }

        // debbugging: output already energized tiles
        for (std::string row : energized_tiles) {
            std::cout << row << '\n';
        }
        std::cout << '\n';

    }

    // count total number of energized tiles
    unsigned int n_energized_tiles = 0;
    for (std::string row : energized_tiles) {
        n_energized_tiles += std::count(row.begin(), row.end(), CHAR_ENERGIZED);
    }
    std::cout << "-> Total number of energized tiles:\n" << n_energized_tiles << '\n';
}