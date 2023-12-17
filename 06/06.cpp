#include <vector>
#include <numeric>
#include <fstream>
#include <iostream>

const std::string INPUT_FILE = "puzzle_input.txt";
const std::string LINE_PREFIX_TIME = "Time:";
const std::string LINE_PREFIX_DISTANCE = "Distance:";


void read_in_numbers_separated_by_spaces(const std::string &line, const std::string &line_begin_str, std::vector<size_t> &numbers)
{
    if (line.rfind(line_begin_str, 0) == 0)
    {
        std::string current_str = "";
        for (std::string::const_iterator it = line.begin(); it <= line.end(); it++)
        {
            //if (std::isdigit(*it) && current_str == "") {
            if (std::isdigit(*it)) {
                current_str += *it;
            }
            if ((*it == ' ' && current_str != "") || (it == line.end() && current_str != "")) {
                numbers.push_back(std::stoi(current_str));
                current_str.clear();
            }
        }
    }
}


int main(int argc, char **argv)
{
    // read in file
    std::ifstream text_file(INPUT_FILE);

    std::vector<size_t> race_times = {};
    std::vector<size_t> race_distances = {};
    std::vector<size_t> number_of_ways_to_beat_the_record = {};

    for (std::string line; std::getline(text_file, line);) {
        std::cout << line << '\n';

        read_in_numbers_separated_by_spaces(line, LINE_PREFIX_TIME, race_times);
        read_in_numbers_separated_by_spaces(line, LINE_PREFIX_DISTANCE, race_distances);

    }

    // naive approach:
    // go from 0 to the amount of time that is maximally possible: the running index is the charging button pressing duration
    // then check 
    for (size_t i = 0; i < race_times.size(); i++) {
        size_t n_beaten_records = 0;
        for (size_t j = 0; j <= race_times[i]; j++) {

            //size_t velocity = i;
            size_t time_left = race_times[i] - j;
            size_t travelled_distance = time_left * j;
            if (travelled_distance > race_distances[i]) {
                n_beaten_records++;
            }
        }
        number_of_ways_to_beat_the_record.push_back(n_beaten_records);
    }

    std::cout << "Number of beaten records:\n";
    for (auto number : number_of_ways_to_beat_the_record) {
        std::cout << number << " | ";
    }
    std::cout << '\n';
    size_t product = std::accumulate(number_of_ways_to_beat_the_record.begin(), number_of_ways_to_beat_the_record.end(), 1, std::multiplies<size_t>());
    std::cout << "---> Product: " << product << '\n';
}