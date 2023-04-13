#include <iostream>
#include "card.hpp"

using namespace std;

namespace ariel {

    Card::Card(int value, CardShape shape): value(value), shape(shape){
        if (value < 1  || value > 13) {
            throw std::invalid_argument("Value incorrect, must to be between 1 to 13.");
        }
    }

    int Card::get_value() {
        return this->value;
    }

    CardShape Card::get_shape() {
        return this->shape;
    }

    bool Card::is_better(Card &other) {
        if (this->get_value() == 2 && other.get_value() == 1){
            return true;
        } else if (this->get_value() == 1){
            return true;
        } else if (this->get_value() > other.get_value()) {
            return true;
        }
        return false;
    }

    bool Card::is_equal(Card &other) {
        if (this->get_value() == other.get_value()){
            return true;
        }
        return false;
    }

    string Card::get_shape_name() {
        switch (this->shape) {
            case CardShape::Club:
                return "Clubs";
            case CardShape::Diamond:
                return "Diamonds";
            case CardShape::Heart:
                return "Hearts";
            case CardShape::Spade:
                return "Spades";
        }
    }

    string Card::get_value_name() {
        switch (this->value) {
            case 13:
                return "king";
            case 12:
                return "Queen";
            case 11:
                return "Jack";
            case 1:
                return "Ace";
            default:
                return to_string(this->value);
        }
    }

}
