//
// Created by Brandon Martin on 8/15/18.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../../src/objects/player.h"
#include "../../src/objects/match.h"

using testing::Eq;

void populateDeck(std::shared_ptr<Deck> deck) {
    for (CardColors color : CARD_COLORS) {
        if (color != CardColors::WILD) {
            for (CardValues value : CARD_VALUES) {
                if (value != CardValues::WILD && value != CardValues::PLUS4) {
                    Card c(color, value, false);
                    deck->pushCard(c);
                }
            }
        }
    }
    Card cWild(CardColors::WILD, CardValues::WILD, true);
    Card cPlus4(CardColors::WILD, CardValues::PLUS4, true);
    for (int i = 0; i < 4; i++) {
        deck->pushCard(cWild);
        deck->pushCard(cPlus4);
    }
}

TEST(match_tests, create_match) {
    std::shared_ptr<Deck> deck (new Deck);
    std::shared_ptr<Deck> pile (new Deck);
    std::shared_ptr<Hand> hand (new Hand);
    std::vector<Player> players;
    Card c(CardColors::BLUE, CardValues::ONE, false);
    hand->addCard(c);
    Player p("Brandon", hand);
    players.push_back(p);
    populateDeck(deck);
    Match m(players, deck, pile);

    Player p1 = m.getPlayers()[0];
    m.getPlayers()[0].addPoints(100);

    ASSERT_EQ(p1.getName(), "Brandon");
    ASSERT_EQ(m.getPlayers()[0].getPoints(), 100);
    ASSERT_EQ(p1.getHand(), hand);
    ASSERT_EQ(p1.getHand()->size(), 1);

    p1.getHand()->removeCard(0);
}

