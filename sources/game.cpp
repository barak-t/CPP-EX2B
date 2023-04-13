#include "iostream"
#include "game.hpp"
#include "card.hpp"

using namespace std;
using namespace ariel;

namespace ariel {

    Game::Game(Player &p1, Player &p2): p1(p1), p2(p2) {
        this->p1 = p1;
        this->p2 = p2;
        this->rest_game();
    }

    void Game::rest_game() {
        this->p1.clean_stack();
        this->p2.clean_stack();
        vector<Card> stack = Card::get_new_stack();

        for (int i = 0; i < 26; i++) {
            this->p1.add_card(stack.back());
            stack.pop_back();
            this->p2.add_card(stack.back());
            stack.pop_back();
        }
    }

    string Game::getStatsForPlayer(Player* player) {
        return player->get_name() + " - wins: " + to_string(this->win_rate[player]) + ". cards won: " + to_string(player->cardesTaken());
    }

    void Game::set_winner() {
        if (this->winner == nullptr) {
            if (p1.cardesTaken() < p2.cardesTaken()) {
                this->winner = &p2;
            } else if (p1.cardesTaken() > p2.cardesTaken()) {
                this->winner = &p1;
            }
        }
    }

    bool Game::is_game_over() {
        if (p1.stacksize() == 0 || p2.stacksize() == 0) {
            this->set_winner();
            return true;
        }
        return false;
    }

    bool Game::is_game_valid() {
        if (&p1 == &p2){
            return false;
        }
        return true;
    }

    void Game::add_log(string log) {
        this->log.push_back(log);
    }

    void Game::printStats() {
        cout << "Player 1: " << this->getStatsForPlayer(&p1) << endl;
        cout << "Player 2: " << this->getStatsForPlayer(&p2) << endl;
        cout << "Draws: " << this->draw_rate << endl;
    }

    void Game::printWiner() {
        if(is_game_over()){
            if(winner == nullptr) {
                cout << "The game end with draw." << endl;
            } else {
                cout << "The winner is " << this->winner->get_name() << endl;
            }
        } else {
            cout << "The game is no over yet." << endl;
        }
    }

    void Game::printLastTurn() {
        if(this->log.size() > 0) {
            cout << log.at(log.size()-1) << endl;
        } else {
            cout << "No Turn has played yet." << endl;
        }
    }

    void Game::playAll() {
        while (!this->is_game_over()) {
            this->playTurn();
        }
    }

    void Game::playTurn() {
        if(!this->is_game_valid()) {
            throw std::runtime_error("Invalid game");
        }
        if(this->is_game_over()) {
            throw std::runtime_error("Game is over");
        }

        vector<Card> turn_cards;
        string l = "";

        Player* turn_winner = nullptr;
        bool turn_running = true;
        while (turn_running) {
            if(this->is_game_over()) {
                return;
            }
            Card p1_card = this->p1.get_card();
            turn_cards.push_back(p1_card);
            Card p2_card = this->p2.get_card();
            turn_cards.push_back(p2_card);
            l += p1.get_name() + " played " + p1_card.get_value_name() + " of " + p1_card.get_shape_name() + ", ";
            l += p2.get_name() + " played " + p2_card.get_value_name() + " of " + p2_card.get_shape_name() + ". ";

            if (!p1_card.is_equal(p2_card)) {
                if (p1_card.is_better(p2_card)) {
                    turn_winner = &this->p1;
                } else {
                    turn_winner = &this->p2;
                }
                l += turn_winner->get_name() + " wins. ";
                break;
            } else { // Equal
                this->draw_rate++;
                l += "Draw. ";

                if (p1.stacksize() == 0 && p2.stacksize() == 0) {
                    if (turn_cards.size() == 2) {
                        p1.add_taken(1);
                        p2.add_taken(1);
                        break;
                    }

                    for(int i=0; i<turn_cards.size()/2; i++) {
                        p1.add_card(turn_cards.back());
                        turn_cards.pop_back();
                    }
                    for(int i=0; i<turn_cards.size(); i++) {
                        p2.add_card(turn_cards.back());
                        turn_cards.pop_back();
                    }
                } else {
                    if(p1.stacksize() > 1 && p2.stacksize() > 1) {
                        // Get two upside down cards
                        turn_cards.push_back(this->p1.get_card());
                        turn_cards.push_back(this->p2.get_card());
                    }
                }
            }
        }
        if(turn_winner != nullptr) {
            turn_winner->add_taken(turn_cards.size());
            this->win_rate[turn_winner]++;
        }
        this->add_log(l);

        is_game_over();
    }

    void Game::printLog() {
        for (size_t i=0; i<this->log.size(); i++) {
            cout << log.at(i) << endl;
        }
    }

}
