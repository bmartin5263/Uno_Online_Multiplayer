//
// Created by Brandon Martin on 8/13/18.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../../src/objects/hand.h"
//#include "../lib/fakeit.hpp"

using testing::Eq;

TEST(hand_tests, create_hand) {
    Hand h;
    ASSERT_EQ(h.size(), 0);
    ASSERT_EQ(h.empty(), true);
}

TEST(hand_tests, add_single_card_to_hand) {
    Hand h;
    ASSERT_EQ(h.size(), 0);
    ASSERT_EQ(h.empty(), true);

    Card c(CardColors::BLUE, CardValues::ONE, false);
    h.addCard(c);

    ASSERT_EQ(h.size(), 1);
    ASSERT_EQ(h.empty(), false);

    Card c2 = h.getCard(0);

    ASSERT_EQ(c2.getValue(), CardValues::ONE);
    ASSERT_EQ(c2.getColor(), CardColors::BLUE);
    ASSERT_EQ(c2.isWild(), false);

}

TEST(hand_tests, pop_single_card) {
    Hand h;
    ASSERT_EQ(h.size(), 0);
    ASSERT_EQ(h.empty(), true);

    Card c(CardColors::BLUE, CardValues::ONE, false);
    h.addCard(c);

    ASSERT_EQ(h.size(), 1);
    ASSERT_EQ(h.empty(), false);

    Card c2 = h.removeCard(0);

    ASSERT_EQ(c2.getValue(), CardValues::ONE);
    ASSERT_EQ(c2.getColor(), CardColors::BLUE);
    ASSERT_EQ(c2.isWild(), false);

    ASSERT_EQ(h.size(), 0);
    ASSERT_EQ(h.empty(), true);
}

TEST(hand_tests, add_multiple_cards_to_hand) {
    Hand h;
    ASSERT_EQ(h.size(), 0);
    ASSERT_EQ(h.empty(), true);

    Card c1(CardColors::BLUE, CardValues::ONE, false);
    Card c2(CardColors::RED, CardValues::TWO, false);
    Card c3(CardColors::GREEN, CardValues::THREE, false);
    h.addCard(c1);
    h.addCard(c2);
    h.addCard(c3);
    ASSERT_EQ(h.size(), 3);
    ASSERT_EQ(h.empty(), false);

    Card c1Popped = h.getCard(0);
    ASSERT_EQ(c1Popped.getValue(), CardValues::ONE);
    ASSERT_EQ(c1Popped.getColor(), CardColors::BLUE);
    ASSERT_EQ(c1Popped.isWild(), false);

    Card c2Popped = h.getCard(1);
    ASSERT_EQ(c2Popped.getValue(), CardValues::TWO);
    ASSERT_EQ(c2Popped.getColor(), CardColors::RED);
    ASSERT_EQ(c2Popped.isWild(), false);

    Card c3Popped = h.getCard(2);
    ASSERT_EQ(c3Popped.getValue(), CardValues::THREE);
    ASSERT_EQ(c3Popped.getColor(), CardColors::GREEN);
    ASSERT_EQ(c3Popped.isWild(), false);

    ASSERT_EQ(h.size(), 3);
    ASSERT_EQ(h.empty(), false);
}

TEST(hand_tests, remove_card_from_middle) {
    Hand h;
    ASSERT_EQ(h.size(), 0);
    ASSERT_EQ(h.empty(), true);

    Card c1(CardColors::BLUE, CardValues::ONE, false);
    Card c2(CardColors::RED, CardValues::TWO, false);
    Card c3(CardColors::GREEN, CardValues::THREE, false);
    h.addCard(c1);
    h.addCard(c2);
    h.addCard(c3);
    ASSERT_EQ(h.size(), 3);
    ASSERT_EQ(h.empty(), false);

    Card c1Popped = h.removeCard(1);
    ASSERT_EQ(c1Popped.getValue(), CardValues::TWO);
    ASSERT_EQ(c1Popped.getColor(), CardColors::RED);
    ASSERT_EQ(c1Popped.isWild(), false);

    Card c2Popped = h.getCard(0);
    ASSERT_EQ(c2Popped.getValue(), CardValues::ONE);
    ASSERT_EQ(c2Popped.getColor(), CardColors::BLUE);
    ASSERT_EQ(c2Popped.isWild(), false);

    Card c3Popped = h.getCard(1);
    ASSERT_EQ(c3Popped.getValue(), CardValues::THREE);
    ASSERT_EQ(c3Popped.getColor(), CardColors::GREEN);
    ASSERT_EQ(c3Popped.isWild(), false);

    ASSERT_EQ(h.size(), 2);
    ASSERT_EQ(h.empty(), false);
}