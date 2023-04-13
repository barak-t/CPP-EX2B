#pragma once
#include <iostream>
#include <algorithm>
#include <vector>
#include <random>


using namespace std;

namespace ariel{

    enum CardShape {
        Club,
        Diamond,
        Heart,
        Spade
    };

    const int max_card_value = 13;

    class Card {

        private:
            CardShape shape;
            int value;

        public:
            CardShape get_shape();
            int get_value();
            Card(int value, CardShape shape);
            bool is_better(Card& other);
            bool is_equal(Card& other);

            string get_shape_name();
            string get_value_name();

            static vector<Card> get_new_stack() {
                vector<Card> stack;
                for(int value=1; value<=max_card_value; value++) {
                    stack.push_back(Card(value, CardShape::Spade));
                    stack.push_back(Card(value, CardShape::Heart));
                    stack.push_back(Card(value, CardShape::Diamond));
                    stack.push_back(Card(value, CardShape::Club));
                }

                auto rng = random_device {};
                shuffle(stack.begin(), stack.end(), rng);

                return stack;
            }
    };
}