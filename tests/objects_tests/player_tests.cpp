//
// Created by Brandon Martin on 8/15/18.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../../src/objects/player.h"

using testing::Eq;

TEST(player_tests, create_player) {
    Hand* h = new Hand();
    Player p("Brandon", h);

    ASSERT_EQ(p.getName(), "Brandon");
    ASSERT_EQ(p.getPoints(), 0);
    ASSERT_EQ(p.getHand(), h);
    ASSERT_EQ(p.getHand()->size(), 0);
}

TEST(player_tests, add_points) {
    Hand* h = new Hand();
    Player p("Brandon", h);

    p.addPoints(100);
    p.addPoints(400);
    p.addPoints(-200);

    ASSERT_EQ(p.getPoints(), 300);
}


TEST(player_tests, add_cards_to_hand) {
    Hand* h = new Hand();
    Player p("Brandon", h);

    { // Enforce Scoping
        Card c1(CardColors::BLUE, CardValues::ONE, false);
        Card c2(CardColors::RED, CardValues::TWO, false);
        Card c3(CardColors::GREEN, CardValues::THREE, false);

        p.getHand()->addCard(c1);
        p.getHand()->addCard(c2);
        p.getHand()->addCard(c3);
    }

    Hand* hand = p.getHand();

    Card c1Popped = hand->getCard(0);
    ASSERT_EQ(c1Popped.getValue(), CardValues::ONE);
    ASSERT_EQ(c1Popped.getColor(), CardColors::BLUE);
    ASSERT_EQ(c1Popped.isWild(), false);
    Card c2Popped = hand->getCard(1);
    ASSERT_EQ(c2Popped.getValue(), CardValues::TWO);
    ASSERT_EQ(c2Popped.getColor(), CardColors::RED);
    ASSERT_EQ(c2Popped.isWild(), false);
    Card c3Popped = hand->getCard(2);
    ASSERT_EQ(c3Popped.getValue(), CardValues::THREE);
    ASSERT_EQ(c3Popped.getColor(), CardColors::GREEN);
    ASSERT_EQ(c3Popped.isWild(), false);
    ASSERT_EQ(hand->size(), 3);
    ASSERT_EQ(hand->empty(), false);
}

TEST(player_tests, copy_player) {
    Hand* h1 = new Hand();
    Player p("Brandon", h1);

    {
        // Enforce Scoping
        Card c1(CardColors::BLUE, CardValues::ONE, false);
        Card c2(CardColors::RED, CardValues::TWO, false);
        Card c3(CardColors::GREEN, CardValues::THREE, false);

        p.getHand()->addCard(c1);
        p.getHand()->addCard(c2);
        p.getHand()->addCard(c3);
    }

    Player p2 = p;

    Hand* hand2 = p2.getHand();

    Card c1Popped = hand2->getCard(0);
    ASSERT_EQ(c1Popped.getValue(), CardValues::ONE);
    ASSERT_EQ(c1Popped.getColor(), CardColors::BLUE);
    ASSERT_EQ(c1Popped.isWild(), false);
    Card c2Popped = hand2->getCard(1);
    ASSERT_EQ(c2Popped.getValue(), CardValues::TWO);
    ASSERT_EQ(c2Popped.getColor(), CardColors::RED);
    ASSERT_EQ(c2Popped.isWild(), false);
    Card c3Popped = hand2->getCard(2);
    ASSERT_EQ(c3Popped.getValue(), CardValues::THREE);
    ASSERT_EQ(c3Popped.getColor(), CardColors::GREEN);
    ASSERT_EQ(c3Popped.isWild(), false);
    ASSERT_EQ(hand2->size(), 3);
    ASSERT_EQ(hand2->empty(), false);

    Card removedCard = hand2->removeCard(0);
    ASSERT_EQ(hand2->size(), 2);

    Hand* hand1 = p.getHand();
    ASSERT_EQ(hand1->size(), 3);
    ASSERT_EQ(hand1->empty(), false);

}

