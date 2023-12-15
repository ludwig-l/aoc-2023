#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <map>
#include <vector>

class SourceDestinationMapping
{
    private:
        unsigned long long _destination_range_start;
        unsigned long long _source_range_start;
        unsigned long long _range_length;

    public:
        SourceDestinationMapping() : _destination_range_start(0), _source_range_start(0), _range_length() {};
        SourceDestinationMapping(unsigned long long destination_range_start, unsigned long long source_range_start, unsigned long long range_length)
        : _destination_range_start(destination_range_start)
        , _source_range_start(source_range_start)
        , _range_length(range_length) {;}

        unsigned long long get_destination_range_start() {return _destination_range_start;}
        unsigned long long get_source_range_start() {return _source_range_start;}
        unsigned long long get_range_length() {return _range_length;}

        void set_destination_range_start(const unsigned long long val) {_destination_range_start = val;}
        void set_source_range_start(const unsigned long long val) {_source_range_start = val;}
        void set_range_length(const unsigned long long val) {_range_length = val;}
};

namespace Utils {

    void extract_mapping_ranges_from_line(SourceDestinationMapping* mapping, const std::string& line) {
        // extract numbers and create and return the respective object for them

        bool is_destination_range_start_set = false;
        bool is_source_range_start_set = false;
        unsigned long long destination_range_start = 0;
        unsigned long long source_range_start = 0;
        unsigned long long range_length = 0;
        std::string current_str = "";
        for (auto it = line.begin(); it <= line.end(); it++) {
            if (isdigit(*it)) {
                current_str += *it;
            }
            if (*it == ' ' || it == line.end()) {
                if (!is_destination_range_start_set && !is_source_range_start_set) {
                    destination_range_start = stoll(current_str);
                    current_str.clear();
                    is_destination_range_start_set = true;
                    continue;
                }
                if (is_destination_range_start_set && !is_source_range_start_set) {
                    source_range_start = stoll(current_str);
                    current_str.clear();
                    is_source_range_start_set = true;
                    continue;
                }
                if (is_destination_range_start_set && is_source_range_start_set) {
                    range_length = stoll(current_str);
                    current_str.clear();
                }
            }
        }
        mapping->set_destination_range_start(destination_range_start);
        mapping->set_source_range_start(source_range_start);
        mapping->set_range_length(range_length);
    }

    void create_map_out_of_mapping_instructions(std::vector<SourceDestinationMapping*>& mappings, std::map<unsigned long long, unsigned long long>& target_map)
    {
        // create a std::map based on the destination and source ranges and range lengths from the available mappings
        for (SourceDestinationMapping* mapping : mappings) {
            for (unsigned long long i = 0; i < mapping->get_range_length(); i++) {
                target_map[mapping->get_source_range_start() + i] = mapping->get_destination_range_start() + i;
            }
        }
    }

}


#endif