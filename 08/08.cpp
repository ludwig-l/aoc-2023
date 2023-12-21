#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
//#include "node.h"


const std::string INPUT_FILE = "puzzle_input.txt";
const unsigned int NODE_NAME_LENGTH = 3;
const char LEFT_OP = 'L';
const char RIGHT_OP = 'R';
const std::string START_NODE = "AAA";
const std::string END_NODE = "ZZZ";


int main(int argc, char** argv)
{
    std::map<std::string, std::map<char, std::string>> nodes;
    std::string op_seq = "";

    // read in file
    std::ifstream text_file(INPUT_FILE);

    bool is_first_line = true;
    for (std::string line; std::getline(text_file, line); ) {
        std::cout << line << '\n';

        if (is_first_line) {
            op_seq = line;
            is_first_line = false;
        }

        if (line.find('=') != std::string::npos) {

            std::istringstream string_stream(line);
            std::string node_name = "";
            std::string node_l_link = "";
            std::string node_r_link = "";
            for (std::string element; std::getline(string_stream, element, ' '); ) {
                if (node_name == "")  {
                    node_name = element;
                }
                if ((element[0] == '(') && (node_l_link == "")) {
                    node_l_link = element.substr(1, NODE_NAME_LENGTH);
                }
                if ((element.back() == ')') && (node_r_link == "")) {
                    node_r_link = element.substr(0, NODE_NAME_LENGTH);
                }
            }

        // create node
        std::map<char, std::string> node = {{LEFT_OP, node_l_link}, {RIGHT_OP, node_r_link}};
        nodes[node_name] = node;
        }
    }

    // traverse the operation sequence
    std::string current_node = START_NODE;
    unsigned int n_steps = 0;
    std::cout << "Traverse operation sequence:\n";
    std::cout << current_node;
    while (current_node != END_NODE) {
        for (char op : op_seq) {
            std::cout << " --(" << op << ")--> ";
            current_node = nodes[current_node][op];
            std::cout << current_node;
            n_steps++;
            if (current_node == END_NODE) {
                break;
            }
        }
    }
    std::cout << "\n-> Number of steps until node " << END_NODE << " was reached: " << n_steps << '\n';
}