#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <map>
#include <vector>

class SourceDestinationMapping
{
    private:
        int _destination_range_start;
        int _source_range_start;
        int _range_length;

    public:
        SourceDestinationMapping() : _destination_range_start(0), _source_range_start(0), _range_length() {};
        SourceDestinationMapping(int destination_range_start, int source_range_start, int range_length)
        : _destination_range_start(destination_range_start)
        , _source_range_start(source_range_start)
        , _range_length(range_length) {;}

        int get_destination_range_start() {return _destination_range_start;}
        int get_source_range_start() {return _source_range_start;}
        int get_range_length() {return _range_length;}

        void set_destination_range_start(const int val) {_destination_range_start = val;}
        void set_source_range_start(const int val) {_source_range_start = val;}
        void set_range_length(const int val) {_range_length = val;}
};

namespace Utils {

    void extract_mapping_ranges_from_line(SourceDestinationMapping* mapping, const std::string& line) {
        // extract numbers and create and return the respective object for them

        unsigned destination_range_start = -1;
        unsigned source_range_start = -1;
        unsigned range_length = -1;
        std::string current_str = "";
        for (auto it = line.begin(); it <= line.end(); it++) {
            if (isdigit(*it)) {
                current_str += *it;
            }
            if (*it == ' ' || it == line.end()) {
                if (destination_range_start == -1 && source_range_start == -1)  {
                    destination_range_start = stol(current_str);
                    current_str.clear();
                    continue;
                }
                if (destination_range_start != -1 && source_range_start == -1) {
                    source_range_start = stol(current_str);
                    current_str.clear();
                    continue;
                }
                if (destination_range_start != -1 && source_range_start != -1 && range_length == -1) {
                    range_length = stol(current_str);
                    current_str.clear();
                }
            }
        }
        mapping->set_destination_range_start(destination_range_start);
        mapping->set_source_range_start(source_range_start);
        mapping->set_range_length(range_length);
    }

    void create_map_out_of_mapping_instructions(std::vector<SourceDestinationMapping*>& mappings, std::map<unsigned long, unsigned long>& target_map)
    {
        // create a std::map based on the destination and source ranges and range lengths from the available mappings
        for (SourceDestinationMapping* mapping : mappings) {
            for (int i = 0; i < mapping->get_range_length(); i++) {
                target_map[mapping->get_source_range_start() + i] = mapping->get_destination_range_start() + i;
            }
        }
    }

}


#endif