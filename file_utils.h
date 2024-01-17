#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <iostream>
#include <fstream>


namespace FileUtils {

    enum class InputFileStatus {
        ok = 0,
        no_input_given,
        input_file_does_not_exist 
    };

    InputFileStatus get_file_status(int argc, char** argv)
    {
        /*
        Checks the status of the given input file.
        */

        // check for given input file, read in file and check for file existance first
        if (argc <= 1) {
            std::cout << "No input file given.\n";
            return InputFileStatus::no_input_given;
        }
        std::ifstream file(argv[1]);

        if (!file.good()) {
            std::cout << "Given text file \"" << argv[1] << "\" does not exist.\n";
            return InputFileStatus::input_file_does_not_exist;
        }
        
        return InputFileStatus::ok;
    }

};


#endif