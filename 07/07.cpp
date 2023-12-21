#include <fstream>
#include <iostream>
#include <sstream>
#include <utility>
#include "utils.h"

const std::string INPUT_FILE = "puzzle_input.txt";
const unsigned int HAND_SIZE = 5;

int main(int argc, char** argv) {

    // read in file
    std::ifstream text_file(INPUT_FILE);

    CamelCards camel_cards = CamelCards(HAND_SIZE);
    std::vector<CamelCards::HandType> hand_types = {};
    std::vector<std::tuple<std::string, unsigned int, CamelCards::HandType>> hands_bids_types = {};

    for (std::string line; std::getline(text_file, line); ) {
        std::cout << line << '\n';

        std::string hand = "";
        unsigned int bid = 0;

        // read in file input and save every line to the data structure
        std::istringstream string_stream(line);
        for (std::string element; std::getline(string_stream, element, ' '); ) {
            if (hand == "" && bid == 0) {
                hand = element;
                continue;
            }
            if (hand != "" && bid == 0) {
                bid = stoi(element);
            }
        }
        // create empty map of character occurences and then fill it up using function
        std::map<char, unsigned int> char_occurences;
        for (char c : *camel_cards.get_card_labels()) {
            char_occurences[c] = 0;
        }
        camel_cards.count_occurences_of_characters(char_occurences, hand);
        std::cout << "Check\n";


        CamelCards::HandType hand_type;
        // assign the respective label (implemented as enumns here) to each hand
        if (camel_cards.is_n_of_a_kind(hand, 5)) {
            hand_type = CamelCards::HandType::five_of_a_kind;
        }
        else if (camel_cards.is_n_of_a_kind(hand, 4)) {
            hand_type = CamelCards::HandType::four_of_a_kind;
        }
        else if (camel_cards.is_full_house(char_occurences)) {
            hand_type = CamelCards::HandType::full_house;
        }
        else if (camel_cards.is_n_of_a_kind(hand, 3)) {
            hand_type = CamelCards::HandType::three_of_a_kind;
        }
        else if (camel_cards.count_number_of_pairs(char_occurences) == 2) {
            hand_type = CamelCards::HandType::two_pair;
        }
        else if (camel_cards.count_number_of_pairs(char_occurences) == 1) {
            hand_type = CamelCards::HandType::one_pair;
        }
        else {
            hand_type = CamelCards::HandType::high_card;
        }

        // add to data structure
        std::tuple<std::string, unsigned int, CamelCards::HandType> hand_bid_type = std::make_tuple(hand, bid, hand_type);
        camel_cards.add_hand_bid_type(hand_bid_type);

    }

    // sort two times:

    // sort by hand types rank
    camel_cards.sort_cards_by_type();

    // sort hands of same type by rule number two
    camel_cards.sort_cards_by_second_ordering_rule();

    // check from highest to lowest kind of hand which hand type does each hand have and assign the respective enum
    unsigned int total_winnings = camel_cards.determine_total_winnings();
    std::cout << "Total winnings: " << total_winnings << '\n';
}