//
// Created by Brandon Martin on 8/13/18.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../../src/objects/deck.h"
//#include "../lib/fakeit.hpp"

using testing::Eq;

TEST(deck_tests, create_deck) {
    Deck d;
    ASSERT_EQ(d.size(), 0);
    ASSERT_EQ(d.empty(), true);
}

TEST(deck_tests, push_single_card) {
    Deck d;
    Card c(CardColors::BLUE, CardValues::ONE, false);
    d.pushCard(c);

    ASSERT_EQ(d.size(), 1);
    ASSERT_EQ(d.empty(), false);

    Card card = d.peekCard();

    ASSERT_EQ(card.getValue(), CardValues::ONE);
    ASSERT_EQ(card.getColor(), CardColors::BLUE);
    ASSERT_EQ(card.isWild(), false);

    // Make sure card was not removed
    ASSERT_EQ(d.size(), 1);
    ASSERT_EQ(d.empty(), false);
}

TEST(deck_tests, push_multiple_cards) {
    Deck d;
    Card c1(CardColors::BLUE, CardValues::ONE, false);
    Card c2(CardColors::RED, CardValues::TWO, false);
    Card c3(CardColors::GREEN, CardValues::THREE, false);
    d.pushCard(c1);
    d.pushCard(c2);
    d.pushCard(c3);
    ASSERT_EQ(d.size(), 3);
    ASSERT_EQ(d.empty(), false);

    CardColors expectedColors[3] = {CardColors::GREEN, CardColors::RED, CardColors::BLUE};
    CardValues expectedValues[3] = {CardValues::THREE, CardValues::TWO, CardValues::ONE};

    for (int i = 0; i < 3; i++) {
        Card c = d.popCard();
        ASSERT_EQ(c.getColor(), expectedColors[i]);
        ASSERT_EQ(c.getValue(), expectedValues[i]);
        ASSERT_EQ(c.isWild(), false);
    }

    ASSERT_EQ(d.size(), 0);
    ASSERT_EQ(d.empty(), true);

}

TEST(deck_tests, deck_copy) {
    Deck d;
    Card c1(CardColors::BLUE, CardValues::ONE, false);
    Card c2(CardColors::RED, CardValues::TWO, false);
    Card c3(CardColors::GREEN, CardValues::THREE, false);
    d.pushCard(c1);
    d.pushCard(c2);
    d.pushCard(c3);
    ASSERT_EQ(d.size(), 3);
    ASSERT_EQ(d.empty(), false);

    Deck d2;
    d2 = d;
    CardColors expectedColors[3] = {CardColors::GREEN, CardColors::RED, CardColors::BLUE};
    CardValues expectedValues[3] = {CardValues::THREE, CardValues::TWO, CardValues::ONE};

    for (int i = 0; i < 3; i++) {
        Card c = d2.popCard();
        ASSERT_EQ(c.getColor(), expectedColors[i]);
        ASSERT_EQ(c.getValue(), expectedValues[i]);
        ASSERT_EQ(c.isWild(), false);
    }

    ASSERT_EQ(d2.size(), 0);
    ASSERT_EQ(d2.empty(), true);
    ASSERT_EQ(d.size(), 3);
    ASSERT_EQ(d.empty(), false);
}