#ifndef SPRING_ARRANGEMENT
#define SPRING_ARRANGEMENT


#include <string>
#include <vector>


class SpringArrangement {

    private:
        std::string _springs;
        std::vector<unsigned int> _group_sizes;
        const char _CHAR_OPERATIONAL = '#';
        const char _CHAR_DAMAGED = '.';
        const char _CHAR_UNKNOWN = '?';

    public:
        SpringArrangement(std::string& springs, std::vector<unsigned int>& group_sizes);
};


SpringArrangement::SpringArrangement(std::string& springs, std::vector<unsigned int>& group_sizes) {
    _springs = springs;
    _group_sizes = group_sizes;
}


#endif