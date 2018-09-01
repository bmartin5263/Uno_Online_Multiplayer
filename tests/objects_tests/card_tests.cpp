//
// Created by Brandon Martin on 8/12/18.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../../src/objects/card.h"
//#include "../lib/fakeit.hpp"

using testing::Eq;

TEST(card_tests, create_card) {
    Card card(CardColors::BLUE, CardValues::ONE);
    ASSERT_EQ(card.getValue(), CardValues::ONE);
    ASSERT_EQ(card.getColor(), CardColors::BLUE);
    ASSERT_EQ(card.isWild(), false);
}

TEST(card_tests, create_wild_card) {
    Card card(CardColors::WILD, CardValues::PLUS4);
    ASSERT_EQ(card.getValue(), CardValues::PLUS4);
    ASSERT_EQ(card.getColor(), CardColors::WILD);
    ASSERT_EQ(card.isWild(), true);
}

TEST(card_tests, get_point_values_for_card) {
    Card card0(CardColors::BLUE, CardValues::ZERO);
    Card card1(CardColors::BLUE, CardValues::ONE);
    Card card2(CardColors::BLUE, CardValues::TWO);
    Card card3(CardColors::BLUE, CardValues::THREE);
    Card card4(CardColors::BLUE, CardValues::FOUR);
    Card card5(CardColors::BLUE, CardValues::FIVE);
    Card card6(CardColors::BLUE, CardValues::SIX);
    Card card7(CardColors::BLUE, CardValues::SEVEN);
    Card card8(CardColors::BLUE, CardValues::EIGHT);
    Card card9(CardColors::BLUE, CardValues::NINE);
    Card cardX(CardColors::BLUE, CardValues::SKIP);
    Card cardPlus2(CardColors::BLUE, CardValues::PLUS2);
    Card cardPlus4(CardColors::BLUE, CardValues::PLUS4);
    Card cardWild(CardColors::BLUE, CardValues::WILD);
    Card cardReverse(CardColors::BLUE, CardValues::REVERSE);
    ASSERT_EQ(Card::getPointValue(card0), 0);
    ASSERT_EQ(Card::getPointValue(card1), 1);
    ASSERT_EQ(Card::getPointValue(card2), 2);
    ASSERT_EQ(Card::getPointValue(card3), 3);
    ASSERT_EQ(Card::getPointValue(card4), 4);
    ASSERT_EQ(Card::getPointValue(card5), 5);
    ASSERT_EQ(Card::getPointValue(card6), 6);
    ASSERT_EQ(Card::getPointValue(card7), 7);
    ASSERT_EQ(Card::getPointValue(card8), 8);
    ASSERT_EQ(Card::getPointValue(card9), 9);
    ASSERT_EQ(Card::getPointValue(cardX), 20);
    ASSERT_EQ(Card::getPointValue(cardPlus2), 20);
    ASSERT_EQ(Card::getPointValue(cardReverse), 20);
    ASSERT_EQ(Card::getPointValue(cardWild), 50);
    ASSERT_EQ(Card::getPointValue(cardPlus4), 50);
}