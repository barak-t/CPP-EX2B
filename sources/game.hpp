#pragma once

#include "iostream"
#include "player.hpp"
#include <map>

using namespace std;


namespace ariel{

    class Game {

        private:
            vector<string> log;
            Player& p1;
            Player& p2;
            Player* winner = nullptr;
            map<Player*, int> win_rate{{&p1, 0}, {&p2, 0}};
            int draw_rate = 0;

            string getStatsForPlayer(Player* player);
            void add_log(string log);
            void rest_game();
            bool is_game_over();
            bool is_game_valid();
            void set_winner();

        public:
            Game(Player&, Player&);
            void playAll();
            void printWiner();
            void printLog();
            void printStats();
            void playTurn();
            void printLastTurn();
    };
};            