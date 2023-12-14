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
    std::vector<long> seed_numbers = {};
    // output location numbers
    std::vector<long> location_numbers = {};

    // maps
    std::map<long, long> seed_to_soil;
    std::map<long, long> soil_to_fertilizer;
    std::map<long, long> fertilizer_to_water;
    std::map<long, long> water_to_light;
    std::map<long, long> light_to_temperature;
    std::map<long, long> temperature_to_humidity;
    std::map<long, long> humidity_to_location;

	std::ifstream text_file(INPUT_FILE);
	std::string line;

	if (!text_file.is_open()) {
		std::cout << "File " << INPUT_FILE << " could not be opened correctly.\n";
        return 1;
	}

    std::string current_str = "";

    // read in line by line
	if (text_file.is_open()) {
		while ( getline(text_file, line) ) {
            if (line.rfind("seeds: ", 0) == 0) {
                for (std::string::iterator it = line.begin(); it <= line.end(); it++) {
                    if (isdigit(*it)) {
                        current_str.push_back(*it);
                    }
                    if (*it == ' ' && !current_str.empty()) {
                        seed_numbers.push_back(std::stol(current_str));
                        current_str.clear();
                    }
                    if (it == line.end()) {
                        seed_numbers.push_back(std::stol(current_str));
                        current_str.clear();
                    }
                }
            }

            if (line.rfind("seed-to-soil map:", 0) == 0) {
                std::vector<SourceDestinationMapping*> mappings = {};
                // add mapping values of lines until an empty line is found
                getline(text_file, line); // go to next line
                while (line != "") {
                    // extract the three numbers from the line
                    SourceDestinationMapping* mapping = new SourceDestinationMapping();
                    Utils::extract_mapping_ranges_from_line(mapping, line);
                    mappings.push_back(mapping);
                    getline(text_file, line); // go to next line
                }
                // create map structure out of all available source-destination mappings
                Utils::create_map_out_of_mapping_instructions(mappings, seed_to_soil);
            }

            if (line.rfind("soil-to-fertilizer map:", 0) == 0) {
                std::vector<SourceDestinationMapping*> mappings = {};
                // add mapping values of lines until an empty line is found
                getline(text_file, line); // go to next line
                while (line != "") {
                    // extract the three numbers from the line
                    SourceDestinationMapping* mapping = new SourceDestinationMapping();
                    Utils::extract_mapping_ranges_from_line(mapping, line);
                    mappings.push_back(mapping);
                    getline(text_file, line); // go to next line
                }
                // create map structure out of all available source-destination mappings
                Utils::create_map_out_of_mapping_instructions(mappings, soil_to_fertilizer);
            }
            if (line.rfind("fertilizer-to-water map:", 0) == 0) {
                std::vector<SourceDestinationMapping*> mappings = {};
                // add mapping values of lines until an empty line is found
                getline(text_file, line); // go to next line
                while (line != "") {
                    // extract the three numbers from the line
                    SourceDestinationMapping* mapping = new SourceDestinationMapping();
                    Utils::extract_mapping_ranges_from_line(mapping, line);
                    mappings.push_back(mapping);
                    getline(text_file, line); // go to next line
                }
                // create map structure out of all available source-destination mappings
                Utils::create_map_out_of_mapping_instructions(mappings, fertilizer_to_water);
            }
            if (line.rfind("water-to-light map:", 0) == 0) {
                std::vector<SourceDestinationMapping*> mappings = {};
                // add mapping values of lines until an empty line is found
                getline(text_file, line); // go to next line
                while (line != "") {
                    // extract the three numbers from the line
                    SourceDestinationMapping* mapping = new SourceDestinationMapping();
                    Utils::extract_mapping_ranges_from_line(mapping, line);
                    mappings.push_back(mapping);
                    getline(text_file, line); // go to next line
                }
                // create map structure out of all available source-destination mappings
                Utils::create_map_out_of_mapping_instructions(mappings, water_to_light);
            }
            if (line.rfind("light-to-temperature map:", 0) == 0) {
                std::vector<SourceDestinationMapping*> mappings = {};
                // add mapping values of lines until an empty line is found
                getline(text_file, line); // go to next line
                while (line != "") {
                    // extract the three numbers from the line
                    SourceDestinationMapping* mapping = new SourceDestinationMapping();
                    Utils::extract_mapping_ranges_from_line(mapping, line);
                    mappings.push_back(mapping);
                    getline(text_file, line); // go to next line
                }
                // create map structure out of all available source-destination mappings
                Utils::create_map_out_of_mapping_instructions(mappings, light_to_temperature);
            }
            if (line.rfind("temperature-to-humidity map:", 0) == 0) {
                std::vector<SourceDestinationMapping*> mappings = {};
                // add mapping values of lines until an empty line is found
                getline(text_file, line); // go to next line
                while (line != "") {
                    // extract the three numbers from the line
                    SourceDestinationMapping* mapping = new SourceDestinationMapping();
                    Utils::extract_mapping_ranges_from_line(mapping, line);
                    mappings.push_back(mapping);
                    getline(text_file, line); // go to next line
                }
                // create map structure out of all available source-destination mappings
                Utils::create_map_out_of_mapping_instructions(mappings, temperature_to_humidity);
            }
            if (line.rfind("humidity-to-location map:", 0) == 0) {
                std::vector<SourceDestinationMapping*> mappings = {};
                // add mapping values of lines until an empty line is found
                getline(text_file, line); // go to next line
                while (line != "") {
                    // extract the three numbers from the line
                    SourceDestinationMapping* mapping = new SourceDestinationMapping();
                    Utils::extract_mapping_ranges_from_line(mapping, line);
                    mappings.push_back(mapping);
                    getline(text_file, line); // go to next line
                }
                // create map structure out of all available source-destination mappings
                Utils::create_map_out_of_mapping_instructions(mappings, humidity_to_location);
            }
        }
    }
    text_file.close();

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

    std::cout << "Location values:\n";
    for (int i = 0; i < seed_numbers.size(); i++) {
        std::cout << "Seed number: " << seed_numbers[i] << " -> Location number: " << location_numbers[i] << '\n';
    }
    std::cout << "Lowest location number: " << *std::min_element(location_numbers.begin(), location_numbers.end()) << '\n';

    // at first check if the value is present in the map; if it is not, then the value stays the same
}