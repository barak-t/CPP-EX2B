#pragma once

#include "iostream"
#include "card.hpp"
#include <vector>

using namespace std;
using namespace ariel;

namespace ariel {

    class Player {

    private:
        string name;
        int cards_taken = 0;
        vector<Card> cards;

    public:
        Player(string name);
        int stacksize();
        int cardesTaken();
        string get_name();
        void add_card(Card &card);
        Card get_card();
        void clean_stack();
        void add_taken(int amount);

    };
}