/**
 * Tests
 * 
 * AUTHOR: Barak Tarab
 */

#include <sstream>
#include "doctest.h"
using namespace std;


#include "sources/game.hpp"
#include "sources/player.hpp"
#include "sources/card.hpp"
using namespace ariel;

TEST_CASE("Test Card"){

    Card c1(1, CardShape::Club);

    CHECK_EQ(1, c1.get_value());
    CHECK_EQ(CardShape::Club, c1.get_shape());
    CHECK_NE(CardShape::Heart, c1.get_shape());

    CHECK_THROWS(Card(0, CardShape::Heart));
    CHECK_THROWS(Card(-1, CardShape::Heart));
    CHECK_THROWS(Card(14, CardShape::Spade));

}

TEST_CASE("Test Player") {

    Player p1("Elad");
    Player p2("Nadav");
    CHECK_EQ(p1.get_name(), "Elad");
    CHECK_EQ(p2.get_name(), "Nadav");

    CHECK_EQ(0, p1.cardesTaken());
    CHECK_EQ(0, p1.stacksize());

    CHECK_EQ(0, p2.cardesTaken());
    CHECK_EQ(0, p2.stacksize());
}

TEST_CASE("Test Game") {
    Player p1("Elad");
    Player p2("Nadav");
    Game g1(p1, p2);

    CHECK_EQ(52, p1.stacksize() + p2.stacksize());
    CHECK_EQ(0, p1.cardesTaken());
    CHECK_EQ(0, p2.cardesTaken());


    g1.playTurn();
    CHECK_LE(p1.stacksize() + p2.stacksize(), 50);
    CHECK_EQ(p1.stacksize(), p2.stacksize());
    CHECK(((p1.cardesTaken() > p2.cardesTaken()) || (p1.cardesTaken() < p2.cardesTaken())));

    g1.playTurn();
    CHECK_LE(p1.stacksize() + p2.stacksize(), 48);

    g1.playAll();
    CHECK(((0 == p1.stacksize()) || (0 == p2.stacksize())));
    CHECK_EQ(52, p1.cardesTaken() + p2.cardesTaken());

}
