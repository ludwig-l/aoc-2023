#include <vector>
#include "../file_utils.h"
#include "node.h"


int main(int argc, char **argv)
{
    if (FileUtils::get_file_status(argc, argv) != FileUtils::InputFileStatus::ok) {
        return -1;
    }
    std::fstream text_file(argv[1]);

    // read in file
    std::vector<std::string> city = {};
    for (std::string line; std::getline(text_file, line);) {

        city.push_back(line);

    }

    // ...
    
}