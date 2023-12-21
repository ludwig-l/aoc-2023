/*
Class is not actually in use; started off with this approach but realized that it is too complicated
for this small task to set up a structure with chained nodes like this
*/
#ifndef NODE_H
#define NODE_H


#include <map>
#include <vector>


class Node {

    private:
        std::string _name;
        std::map<char, *Node> _links;

    public:
        Node(std::string name) : _name(name) {;}
        void add_link(char instruction, Node* node) {_links[instruction] = node};

};


#endif
