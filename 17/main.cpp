#include <vector>
#include <utility>
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

    // define start and end positions
    const std::pair<int, int> start_position = std::make_pair(0, 0);
    const std::pair<int, int> end_position = std::make_pair(city.size(), city.front().size());
    
    // create 2D array of nodes
    std::vector<std::vector<Node>> nodes = {};
    for (int i = 0; i < city.size(); i++) {
        nodes.push_back({});
        for (int j = 0; j < city.front().size(); j++) {
            
            nodes[i].push_back(Node());

        }
    }
    // go through all nodes and set the respective attributes and adjacent nodes
    for (int i = 0; i < city.size(); i++) {
        for (int j = 0; j < city.front().size(); j++) {

            if (std::make_pair(i, j) == start_position) {
                nodes[i][j].set_is_start_node(true);
            }
            if (std::make_pair(i, j) == end_position) {
                nodes[i][j].set_is_end_node(true);
            }
            nodes[i][j].set_pos(std::make_pair<unsigned int, unsigned int>(i, j));
            if ((i == 0) && (j == 0)) { // top-left corner node
                nodes[i][j].set_adjacent_nodes({
                    &nodes[0][1],
                    &nodes[1][0]
                });
            }
            else if ((i == 0) && (j == city.front().size()-1)) { // top-right corner node
                nodes[i][j].set_adjacent_nodes({
                    &nodes[0][j-1],
                    &nodes[1][j]
                });
            }
            else if ((i == city.size()-1) && (j == 0)) { // bottom-left corner node
                nodes[i][j].set_adjacent_nodes({
                    &nodes[i-1][0],
                    &nodes[i][1]
                });
            }
            else if ((i == city.size()-1) && (j == city.front().size()-1)) { // bottom-right corner node
                nodes[i][j].set_adjacent_nodes({
                    &nodes[city.size()-2][city.front().size()-1],
                    &nodes[city.size()-1][city.front().size()-2]
                });
            }
            else if (i == 0) { // node on the left outside edge
                nodes[i][j].set_adjacent_nodes({
                    &nodes[i-1][0],
                    &nodes[i][1],
                    &nodes[i+1][0]
                });
            }
            else if (i == city.front().size()-1) { // node on the right outside edge
                nodes[i][j].set_adjacent_nodes({
                    &nodes[i-1][city.front().size()-1],
                    &nodes[i][city.front().size()-1],
                    &nodes[i+1][city.front().size()-1]
                });
            }
            else if (j == 0) { // node on the upper outside edge
                nodes[i][j].set_adjacent_nodes({
                    &nodes[0][j+1],
                    &nodes[1][j],
                    &nodes[0][j-1]
                });
            }
            else if (j == city.size()-1) { // node on the bottom outside edge
                nodes[i][j].set_adjacent_nodes({
                    &nodes[city.size()][j+1],
                    &nodes[city.size()+1][j],
                    &nodes[city.size()][j-1]
                });
            }
            else { // generic case
                std::vector<Node*> adjacent_nodes = {
                    &nodes[i-1][j],
                    &nodes[i][j+1],
                    &nodes[i+1][j],
                    &nodes[i][j-1]
                };
                nodes[i][j].set_adjacent_nodes(adjacent_nodes);
            }

            // set the cost of a node to the respective number in the city map
            nodes[i][j].set_cost(int(city[i][j]));

        }
    }

}
