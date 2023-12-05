// task:
// Calculate the sum of all the numbers contained in the puzzle input file

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>

const std::string INPUT_FILE = "puzzle_input.txt";


int extract_number_from_string(const std::string& str) {
	/*Extracts a number from a given string using a certain pattern.*/

	char first_digit;
	char second_digit;

	// walk from first character forward-wise and stop at the first digit
	for (auto it = str.begin(); it != str.end(); it++) {
		if (isdigit(*it)) {
			first_digit = *it;
			break;
		}
	}

	// reverse string in order to walk it in the same way like before
	std::string str_reverse(str);
	std::reverse(str_reverse.begin(), str_reverse.end());
	for (auto it = str_reverse.begin(); it != str_reverse.end(); it++) {
		if (isdigit(*it)) {
			second_digit = *it;
			break;
		}
	}

	// concatenate numbers and return integer
	std::string number({first_digit, second_digit});
	std::cout << "Line input: " << str << " ---> " << first_digit << " | " << second_digit << "\n";
	return stoi(number);
}


int main(int argc, char** argv)
{
	// define necessary objects
	std::vector<int> list_of_numbers = {};

	// read in the input text file and save each line as an entry of a std::vector
	std::ifstream text_file(INPUT_FILE);
	std::string line;

	if (!text_file.is_open()) {
		std::cout << "File " << INPUT_FILE << " could not be opened correctly.\n";
	}

	if (text_file.is_open()) {
		while ( getline(text_file, line) )
		{
			// extract the respective number from the string
			list_of_numbers.push_back(extract_number_from_string(line));
		}
	}
    text_file.close();

	// final summation
	int sum_of_elemts = std::accumulate(list_of_numbers.begin(), list_of_numbers.end(),
									   decltype(list_of_numbers)::value_type(0));

	// print result
	std::cout << "Result: " << sum_of_elemts << "\n";

	return 0;
}
