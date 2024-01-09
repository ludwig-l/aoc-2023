#ifndef SPRING_ARRANGEMENT
#define SPRING_ARRANGEMENT


#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <bitset>
#include <cassert>


class SpringArrangement {

    private:
        std::string _springs;
        std::vector<unsigned int> _group_sizes;
        std::vector<std::string> _arrangement_combinations;
        const char _CHAR_OPERATIONAL = '#';
        const char _CHAR_DAMAGED = '.';
        const char _CHAR_UNKNOWN = '?';
        enum class SpringMode {
            DAMAGED = 0,
            OPERATIONAL,
        };

    public:
        SpringArrangement(std::string& springs, std::vector<unsigned int>& group_sizes);
        void create_spring_arrangement_combinations(std::vector<std::string>& combs);
        void create_binary_vector_permutations(std::vector<std::string>& perms, const unsigned int n);
};


SpringArrangement::SpringArrangement(std::string& springs, std::vector<unsigned int>& group_sizes) {
    _springs = springs;
    _group_sizes = group_sizes;
    std::vector<std::string> perms = {};
    create_binary_vector_permutations(perms, 4);
    std::vector<std::string> combs = {};
    create_spring_arrangement_combinations(combs);
}


void SpringArrangement::create_spring_arrangement_combinations(std::vector<std::string>& combs)
{
    std::vector<unsigned int> indices_unknown = {};
    std::string::iterator it = _springs.begin();

    // find indices of unknown springs
    while (true) {
        it = std::find(it, _springs.end(), _CHAR_UNKNOWN);
        unsigned int idx = it - _springs.begin();
        if (it == _springs.end()) {
            break;
        }
        indices_unknown.push_back(idx);
        it = it + 1;
    }

    std::vector<std::string> permutations = {};
    create_binary_vector_permutations(permutations, indices_unknown.size());

    // go through all permutations and assign the respective characters
    for (std::string perm : permutations) {
        assert(perm.size() == indices_unknown.size() && "Size of permutation vector and list of unknown indices is not the same.");
        std::string current_str = _springs;
        unsigned int count = 0;
        for (char idx : perm) {
            if (idx == '0') {
                current_str[indices_unknown[count]] = _CHAR_DAMAGED;
            }
            else if (idx == '1') {
                current_str[indices_unknown[count]] = _CHAR_OPERATIONAL;
            }
            else {
                std::cout << "This should not happen.\n";
            }
            count++;
        }
        _arrangement_combinations.push_back(current_str);
    }
}

void SpringArrangement::create_binary_vector_permutations(std::vector<std::string>& perms, const unsigned int n)
{
    // create a vector of strings of all binary permutations for a given size

    for (unsigned int i = 0; i < pow(2, n); i++) {
        std::bitset<32> bits(i); // bitset size needs to be known at compile time, 32 bits should be large enough
        std::string bits_str = bits.to_string();
        perms.push_back(bits_str.substr(bits_str.size()-n, bits_str.size()-1));
    }

}


#endif