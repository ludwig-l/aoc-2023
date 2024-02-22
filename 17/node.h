#ifndef NODE_H
#define NODE_H


#include <limits>
#include <utility>


class Node {
    private:
        bool _is_start_node;
        bool _is_end_node;
        std::pair<unsigned int, unsigned int> _pos;
        std::vector<Node*> _adjacent_nodes;
        unsigned int _cost; // cost value for moving to this node

    public:
        Node() : _is_start_node(false), _is_end_node(false), _pos(std::make_pair(std::numeric_limits<unsigned int>::max(), std::numeric_limits<unsigned int>::max())), _adjacent_nodes(std::vector<Node*>()), _cost(0) {;}
        Node(bool is_start_node, bool is_end_node, std::pair<unsigned int, unsigned int>& pos, std::vector<Node*>& adjacent_nodes, unsigned int cost) : _is_start_node(is_start_node), _is_end_node(is_end_node), _pos(pos), _adjacent_nodes(adjacent_nodes), _cost(cost) {
            if ((_is_start_node == true ) && (_is_end_node == true)) {
                std::cout << "Warning: Node set to be both start and end node. This does not make sense for this application.\n";
            }
        }

};

#endif
