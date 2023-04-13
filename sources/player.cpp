#include "iostream"
#include "player.hpp"
#include "card.hpp"

using namespace std;
using namespace ariel;

namespace ariel {

    Player::Player(string name) {
        this->name = name;
    }

    int Player::cardesTaken() {
        return this->cards_taken;
    }

    int Player::stacksize() {
        return this->cards.size();
    }

    string Player::get_name() {
        return this->name;
    }

    void Player::add_card(Card& card) {
        this->cards.emplace_back(card);
    }

    Card Player::get_card() {
        if (this->cards.size() == 0) {
            throw std::runtime_error("Empty stack");
        }
        Card& c = this->cards.back();
        this->cards.pop_back();
        return c;
    }

    void Player::clean_stack() {
        this->cards.clear();
        this->cards_taken = 0;
    }

    void Player::add_taken(int amount) {
        this->cards_taken += amount;
    }

}
