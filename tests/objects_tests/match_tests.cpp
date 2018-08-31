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
    Deck* deck = new Deck();
    Deck* pile = new Deck();

    std::vector<std::unique_ptr<Player>> players;

    Match m(players, deck, pile);

    ASSERT_EQ(m.getPlayers().size(), 0);
    ASSERT_EQ(m.getPile()->size(), 0);
    ASSERT_EQ(m.getDeck()->size(), 0);
    ASSERT_EQ(m.getTurn(), 0);
    ASSERT_EQ(m.isReversed(), false);
    ASSERT_EQ(m.isComplete(), false);
    ASSERT_EQ(m.isAborted(), false);
}

