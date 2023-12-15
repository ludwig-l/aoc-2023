#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "utils.h"

const std::string INPUT_FILE = "puzzle_input.txt";

int main(int argc, char **argv)
{
    // input seed values
    std::vector<unsigned long long> seed_numbers = {};
    // output numbers
    std::vector<unsigned long long> soil_numbers = {};
    std::vector<unsigned long long> fertilizer_numbers = {};
    std::vector<unsigned long long> water_numbers = {};
    std::vector<unsigned long long> light_numbers = {};
    std::vector<unsigned long long> temperature_numbers = {};
    std::vector<unsigned long long> humidity_numbers = {};
    std::vector<unsigned long long> location_numbers = {};

    // maps
    //std::map<long, long> seed_to_soil;
    //std::map<long, long> soil_to_fertilizer;
    //std::map<long, long> fertilizer_to_water;
    //std::map<long, long> water_to_light;
    //std::map<long, long> light_to_temperature;
    //std::map<long, long> temperature_to_humidity;
    //std::map<long, long> humidity_to_location;

	std::ifstream text_file(INPUT_FILE);
	std::string line;

	if (!text_file.is_open()) {
		std::cout << "File " << INPUT_FILE << " could not be opened correctly.\n";
        return 1;
	}

    std::string current_str = "";

    // read in line by line
	if (text_file.is_open()) {

        // extract the seed numbers at first
        while (getline(text_file, line)) {
            if (line.rfind("seeds: ", 0) == 0) {
                for (std::string::iterator it = line.begin(); it <= line.end(); it++) {
                    if (isdigit(*it)) {
                        current_str.push_back(*it);
                    }
                    if (*it == ' ' && !current_str.empty()) {
                        seed_numbers.push_back(std::stoll(current_str));
                        current_str.clear();
                    }
                    if (it == line.end()) {
                        seed_numbers.push_back(std::stoll(current_str));
                        current_str.clear();
                        break;
                    }
                }
            }
        }

        // reset to beginning of fstream
        text_file.clear();
        text_file.seekg(0);

        // just go through the file several times for each seed
        unsigned int iteration = 0;
        for (std::vector<unsigned long long>::iterator it_seed_number = seed_numbers.begin(); it_seed_number < seed_numbers.end(); it_seed_number++) {
            std::cout << "Check iteration " << iteration << '\n';

            while (getline(text_file, line)) {

                // seed -> soil
                if (line.rfind("seed-to-soil map:", 0) == 0) {
                    // add mapping values of lines until an empty line is found
                    getline(text_file, line); // go to next line
                    while (line != "") {

                        // extract current source-destination mapping from line
                        SourceDestinationMapping* mapping = new SourceDestinationMapping();
                        Utils::extract_mapping_ranges_from_line(mapping, line);

                        // add number to the vector if it is found in the range of source values
                        if ((mapping->get_source_range_start() <= *it_seed_number) && (*it_seed_number <= mapping->get_source_range_start()+(mapping->get_range_length()-1))) {
                            soil_numbers.push_back(mapping->get_destination_range_start() + (*it_seed_number - mapping->get_source_range_start()));
                        }
                        getline(text_file, line);
                    }
                    // if value hasn't been added yet, i.e. if it is not present in the map, add it
                    if (soil_numbers.size() != iteration + 1) {
                        soil_numbers.push_back(*it_seed_number);
                    }
                }
            }
            // reset to beginning of fstream
            text_file.clear();
            text_file.seekg(0);
            

            // soil -> fertilizer
            while (getline(text_file, line)) {

                if (line.rfind("soil-to-fertilizer map:", 0) == 0) {
                    // add mapping values of lines until an empty line is found
                    getline(text_file, line); // go to next line
                    while (line != "") {

                        // extract current source-destination mapping from line
                        SourceDestinationMapping* mapping = new SourceDestinationMapping();
                        Utils::extract_mapping_ranges_from_line(mapping, line);

                        // add number to the vector if it is found in the range of source values
                        if ((mapping->get_source_range_start() <= soil_numbers[iteration]) && (soil_numbers[iteration] <= mapping->get_source_range_start()+(mapping->get_range_length()-1))) {
                            fertilizer_numbers.push_back(mapping->get_destination_range_start() + (soil_numbers[iteration] - mapping->get_source_range_start()));
                        }
                        getline(text_file, line);
                    }
                    // if value hasn't been added yet, i.e. if it is not present in the map, add it
                    if (fertilizer_numbers.size() != iteration + 1) {
                        fertilizer_numbers.push_back(soil_numbers[iteration]);
                    }
                }
            }
            // reset to beginning of fstream
            text_file.clear();
            text_file.seekg(0);


            // fertilizer -> water
            while (getline(text_file, line)) {

                if (line.rfind("fertilizer-to-water map:", 0) == 0) {
                    // add mapping values of lines until an empty line is found
                    getline(text_file, line); // go to next line
                    while (line != "") {

                        // extract current source-destination mapping from line
                        SourceDestinationMapping* mapping = new SourceDestinationMapping();
                        Utils::extract_mapping_ranges_from_line(mapping, line);

                        // add number to the vector if it is found in the range of source values
                        if ((mapping->get_source_range_start() <= fertilizer_numbers[iteration]) && (fertilizer_numbers[iteration] <= mapping->get_source_range_start()+(mapping->get_range_length()-1))) {
                            water_numbers.push_back(mapping->get_destination_range_start() + (fertilizer_numbers[iteration] - mapping->get_source_range_start()));
                        }
                        getline(text_file, line);
                    }
                    // if value hasn't been added yet, i.e. if it is not present in the map, add it
                    if (water_numbers.size() != iteration + 1) {
                        water_numbers.push_back(fertilizer_numbers[iteration]);
                    }
                }
            }
            // reset to beginning of fstream
            text_file.clear();
            text_file.seekg(0);


            // water -> light
            while (getline(text_file, line)) {

                if (line.rfind("water-to-light map:", 0) == 0) {
                    // add mapping values of lines until an empty line is found
                    getline(text_file, line); // go to next line
                    while (line != "") {

                        // extract current source-destination mapping from line
                        SourceDestinationMapping* mapping = new SourceDestinationMapping();
                        Utils::extract_mapping_ranges_from_line(mapping, line);

                        // add number to the vector if it is found in the range of source values
                        if ((mapping->get_source_range_start() <= water_numbers[iteration]) && (water_numbers[iteration] <= mapping->get_source_range_start()+(mapping->get_range_length()-1))) {
                            light_numbers.push_back(mapping->get_destination_range_start() + (water_numbers[iteration] - mapping->get_source_range_start()));
                        }
                        getline(text_file, line);
                    }
                    // if value hasn't been added yet, i.e. if it is not present in the map, add it
                    if (light_numbers.size() != iteration + 1) {
                        light_numbers.push_back(water_numbers[iteration]);
                    }
                }
            }
            // reset to beginning of fstream
            text_file.clear();
            text_file.seekg(0);


            // light -> temperature
            while (getline(text_file, line)) {

                if (line.rfind("light-to-temperature map:", 0) == 0) {
                    // add mapping values of lines until an empty line is found
                    getline(text_file, line); // go to next line
                    while (line != "") {

                        // extract current source-destination mapping from line
                        SourceDestinationMapping* mapping = new SourceDestinationMapping();
                        Utils::extract_mapping_ranges_from_line(mapping, line);

                        // add number to the vector if it is found in the range of source values
                        if ((mapping->get_source_range_start() <= light_numbers[iteration]) && (light_numbers[iteration] <= mapping->get_source_range_start()+(mapping->get_range_length()-1))) {
                            temperature_numbers.push_back(mapping->get_destination_range_start() + (light_numbers[iteration] - mapping->get_source_range_start()));
                        }
                        getline(text_file, line);
                    }
                    // if value hasn't been added yet, i.e. if it is not present in the map, add it
                    if (temperature_numbers.size() != iteration + 1) {
                        temperature_numbers.push_back(light_numbers[iteration]);
                    }
                }
            }
            // reset to beginning of fstream
            text_file.clear();
            text_file.seekg(0);


            // temperature -> humidity
            while (getline(text_file, line)) {

                if (line.rfind("temperature-to-humidity map:", 0) == 0) {
                    // add mapping values of lines until an empty line is found
                    getline(text_file, line); // go to next line
                    while (line != "") {

                        // extract current source-destination mapping from line
                        SourceDestinationMapping* mapping = new SourceDestinationMapping();
                        Utils::extract_mapping_ranges_from_line(mapping, line);

                        // add number to the vector if it is found in the range of source values
                        if ((mapping->get_source_range_start() <= temperature_numbers[iteration]) && (temperature_numbers[iteration] <= mapping->get_source_range_start()+(mapping->get_range_length()-1))) {
                            humidity_numbers.push_back(mapping->get_destination_range_start() + (temperature_numbers[iteration] - mapping->get_source_range_start()));
                        }
                        getline(text_file, line);
                    }
                    // if value hasn't been added yet, i.e. if it is not present in the map, add it
                    if (humidity_numbers.size() != iteration + 1) {
                        humidity_numbers.push_back(temperature_numbers[iteration]);
                    }
                }
            }
            // reset to beginning of fstream
            text_file.clear();
            text_file.seekg(0);


            // humidity -> location
            while (getline(text_file, line)) {

                if (line.rfind("humidity-to-location map:", 0) == 0) {
                    // add mapping values of lines until an empty line is found
                    getline(text_file, line); // go to next line
                    while (line != "") {

                        // extract current source-destination mapping from line
                        SourceDestinationMapping* mapping = new SourceDestinationMapping();
                        Utils::extract_mapping_ranges_from_line(mapping, line);

                        // add number to the vector if it is found in the range of source values
                        if ((mapping->get_source_range_start() <= humidity_numbers[iteration]) && (humidity_numbers[iteration] <= mapping->get_source_range_start()+(mapping->get_range_length()-1))) {
                            location_numbers.push_back(mapping->get_destination_range_start() + (humidity_numbers[iteration] - mapping->get_source_range_start()));
                        }
                        getline(text_file, line);
                    }
                    // if value hasn't been added yet, i.e. if it is not present in the map, add it
                    if (location_numbers.size() != iteration + 1) {
                        location_numbers.push_back(humidity_numbers[iteration]);
                    }
                }
            }
            // reset to beginning of fstream
            text_file.clear();
            text_file.seekg(0);
            

            // iterate running index after one run through all kinds of numbers (soil, fertilizer, ..., location)
            iteration++;
        }

    }
    text_file.close();

    /*
    // go through the maps one by one using the seed numbers as input
    int soil_number = -1;
    int fertilizer_number = -1;
    int water_number = -1;
    int light_number = -1;
    int temperature_number = -1;
    int humidity_number = -1;
    int location_number = -1;

    //for (const int seed_number : seed_numbers) {
    for (std::vector<long>::iterator it = seed_numbers.begin(); it < seed_numbers.end(); it++) {

        // seed -> soil
        if (seed_to_soil.find(*it) != seed_to_soil.end()) {
            soil_number = seed_to_soil.at(*it);
        }
        else {
            soil_number = *it;
        }

        // soil -> fertilizer
        if (soil_to_fertilizer.find(soil_number) != soil_to_fertilizer.end()) {
            fertilizer_number = soil_to_fertilizer.at(soil_number);
        }
        else {
            fertilizer_number = soil_number;
        }

        // fertilizer -> water
        if (fertilizer_to_water.find(fertilizer_number) != fertilizer_to_water.end()) {
            water_number = fertilizer_to_water.at(fertilizer_number);
        }
        else {
            water_number = fertilizer_number;
        }
        
        // water -> light
        if (water_to_light.find(water_number) != water_to_light.end()) {
            light_number = water_to_light.at(water_number);
        }
        else {
            light_number = water_number;
        }

        // light -> temperature
        if (light_to_temperature.find(light_number) != light_to_temperature.end()) {
            temperature_number = light_to_temperature.at(light_number);
        }
        else {
            temperature_number = light_number;
        }

        // temperature -> humidity
        if (temperature_to_humidity.find(temperature_number) != temperature_to_humidity.end()) {
            humidity_number = temperature_to_humidity.at(temperature_number);
        }
        else {
            humidity_number = temperature_number;
        }

        // humidity -> location
        if (humidity_to_location.find(humidity_number) != humidity_to_location.end()) {
            location_number = humidity_to_location.at(humidity_number);
        }
        else {
            location_number = humidity_number;
        }

        location_numbers.push_back(location_number);
        std::cout << "Check\n";
        //int soil_number = seed_to_soil[seed_number];
        //int fertilizer_number = soil_to_fertilizer[soil_number];
        // ...
        //int location_number = humidity_to_location[humidity_number];
    }
    */

    std::cout << "Location values:\n";
    for (size_t i = 0; i < seed_numbers.size(); i++) {
        std::cout << "Seed number: " << seed_numbers[i] << " -> Location number: " << location_numbers[i] << '\n';
    }
    std::cout << "Lowest location number: " << *std::min_element(location_numbers.begin(), location_numbers.end()) << '\n';
}