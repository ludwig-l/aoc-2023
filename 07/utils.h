#ifndef UTILS_H
#define UTILS_H


#include <vector>
#include <map>
#include <utility>
#include <algorithm>


class CamelCards {
    public:
        enum class HandType {
            high_card = 0,
            one_pair,
            two_pair,
            three_of_a_kind,
            full_house,
            four_of_a_kind,
            five_of_a_kind
        };

    private:
        const std::vector<char> _CARD_LABELS = {'A', 'K', 'Q', 'J', 'T', '9', '8', '7', '6', '5', '4', '3', '2'};
        unsigned int _hand_size;
        std::vector<std::tuple<std::string, unsigned int, CamelCards::HandType>> _hands_bids_types;

    public:
        CamelCards(unsigned int hand_size) : _hand_size(hand_size) {;}
        const std::vector<char>* get_card_labels() {return &_CARD_LABELS;}
        void add_hand_bid_type(const std::tuple<std::string, unsigned int, CamelCards::HandType>& hand_bid_type) {_hands_bids_types.push_back(hand_bid_type);}
        bool is_full_house(const std::map<char, unsigned int>& char_occurences);
        unsigned int count_number_of_pairs(const std::map<char, unsigned int>& char_occurences);
        bool is_n_of_a_kind(std::string& hand, unsigned int n);
        void count_occurences_of_characters(std::map<char, unsigned int>& occurences, const std::string& hand);
        int compare_hands_by_second_ordering_rule(std::string& hand1, std::string& hand2);
        void sort_cards_by_type();
        void sort_cards_by_second_ordering_rule();
        unsigned int determine_total_winnings();
};

bool CamelCards::is_n_of_a_kind(std::string& hand, unsigned int n) {

    // brute force style solution for finding n cards of the same kind
    for (char card : _CARD_LABELS) {
        unsigned int n_multiples = 0;
        for (char c : hand) {
            if (c == card) {
                n_multiples++;
            }
        }
        if (n_multiples == n) {
            return true;
        }
    }
    return false;

}

void CamelCards::count_occurences_of_characters(std::map<char, unsigned int>& occurences, const std::string& hand)
{
    for (std::pair<char, unsigned int> char_and_count : occurences) {
        occurences[std::get<0>(char_and_count)] = std::count(hand.begin(), hand.end(), std::get<0>(char_and_count));
    }
}

bool CamelCards::is_full_house(const std::map<char, unsigned int>& char_occurences)
{
    bool found_triple = false;
    bool found_double = false;

    // search for triple and double occurences in the map values
    for (auto it = char_occurences.begin(); it != char_occurences.end(); ++it) {
        if (it->second == 3) {
            found_triple = true;
        }
    }
    for (auto it = char_occurences.begin(); it != char_occurences.end(); ++it) {
        if (it->second == 2) {
            found_double = true;
        }
    }

    if (found_double && found_triple) {
        return true;
    }
    else {
        return false;
    }
}

unsigned int CamelCards::count_number_of_pairs(const std::map<char, unsigned int>& char_occurences)
{
    unsigned int n_pairs = 0;
    for (auto it = char_occurences.begin(); it != char_occurences.end(); ++it) {
        if (it->second == 2) {
            n_pairs++;
        }
    }

    return n_pairs;
}

int CamelCards::compare_hands_by_second_ordering_rule(std::string& hand1, std::string& hand2)
{
    // determine hand labels and return 0 (hand1 rank is higher), 1 (hand2 rank is higher) or -1 (both hands are exactly the same)
    
    // go through each card of the two hands
    for (unsigned int i = 0; i < _hand_size; i++) {
        unsigned int hand1_rank = std::find(_CARD_LABELS.begin(), _CARD_LABELS.end(), hand1[i]) - _CARD_LABELS.begin();
        unsigned int hand2_rank = std::find(_CARD_LABELS.begin(), _CARD_LABELS.end(), hand2[i]) - _CARD_LABELS.begin();
        if (hand1_rank < hand2_rank) {
            return 0;
        }
        else if (hand2_rank < hand1_rank) {
            return 1;
        }
        else if (hand1_rank == hand2_rank && i == _hand_size - 1) {
            return -1;
        }
    }
}

void CamelCards::sort_cards_by_type()
{
    // sort array using rank defined by enums using a lambda expression
    std::sort(_hands_bids_types.begin(), _hands_bids_types.end(),
              [&](std::tuple<std::string, unsigned int, CamelCards::HandType> &a,
                  std::tuple<std::string, unsigned int, CamelCards::HandType> &b)
              {
                  return std::get<2>(a) < std::get<2>(b);
              });
}

void CamelCards::sort_cards_by_second_ordering_rule()
{
    // for starters just go through all the entries and compare two neighboring ones at a time
    
    for (auto it = _hands_bids_types.begin(); it < _hands_bids_types.end(); it++) {

        // break if the current element is already the last one
        if (it+1 == _hands_bids_types.end()) {
            break;
        }

        // check if the current and the next element have the same hand type, otherwise skip current iteration
        if (std::get<2>(*it) != std::get<2>(*(it+1))) {
            continue;
        }

        int higher_hand = this->compare_hands_by_second_ordering_rule(std::get<0>(*it), std::get<0>(*(it+1)));

        // switch current and next element if the next element has a lower card rank
        // reset iterator to start
        if (higher_hand == 0) {
            std::swap(*it, *(it+1));
            it = _hands_bids_types.begin() - 1; // -1 because in the next iteration the iterator will be incremented again
        }

    }
}

unsigned int CamelCards::determine_total_winnings()
{
    unsigned int total_winnings = 0;
    for (unsigned int i = 0; i < _hands_bids_types.size(); i++) {
        total_winnings += (i+1) * std::get<1>(_hands_bids_types[i]);
    }
    return total_winnings;
}

#endif