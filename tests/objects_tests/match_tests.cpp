//
// Created by Brandon Martin on 8/15/18.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../../src/objects/player.h"
#include "../../src/objects/match.h"

using testing::Eq;

void populateDeck(Deck& deck) {
    for (CardColors color : CARD_COLORS) {
        if (color != CardColors::WILD) {
            for (CardValues value : CARD_VALUES) {
                if (value != CardValues::WILD && value != CardValues::PLUS4) {
                    Card c(color, value, false);
                    deck.pushCard(c);
                    if (value != CardValues::ZERO) {
                        deck.pushCard(c);
                    }
                }
            }
        }
    }
    Card cWild(CardColors::WILD, CardValues::WILD, true);
    Card cPlus4(CardColors::WILD, CardValues::PLUS4, true);
    for (int i = 0; i < 4; i++) {
        deck.pushCard(cWild);
        deck.pushCard(cPlus4);
    }
}

TEST(match_tests, create_match) {
    Deck* deck = new Deck();
    Deck* pile = new Deck();

    std::vector<std::unique_ptr<Player>> players;

    {
        Match m(players, deck, pile);

        ASSERT_EQ(m.getPlayers().size(), 0);
        ASSERT_EQ(m.getPile()->size(), 0);
        ASSERT_EQ(m.getDeck()->size(), 0);
        ASSERT_EQ(m.getTurn(), 0);
        ASSERT_EQ(m.isReversed(), false);
        ASSERT_EQ(m.isComplete(), false);
        ASSERT_EQ(m.isAborted(), false);
    }

}

TEST(match_tests, create_match_with_players) {
    Deck* deck = new Deck();
    Deck* pile = new Deck();
    Hand* h1 = new Hand();
    Hand* h2 = new Hand();

    std::vector<std::unique_ptr<Player>> players;

    std::unique_ptr<Player> p1(new Player("Brandon", h1));
    std::unique_ptr<Player> p2(new Player("Mark", h2));
    puts("Players Created");

    players.push_back(std::move(p1));
    players.push_back(std::move(p2));

    {
        Match m(players, deck, pile);
        puts("Match Created");

        ASSERT_EQ(m.getPlayers().size(), 2);
        ASSERT_EQ(m.getPlayer(0)->getName(), "Brandon");
        ASSERT_EQ(m.getPlayer(1)->getName(), "Mark");
    }
    puts("Match Destroyed");

    ASSERT_EQ(players.size(), 2);
    ASSERT_EQ(players[0]->getName(), "Brandon");
    ASSERT_EQ(players[1]->getName(), "Mark");
}

TEST(match_tests, draw_cards_from_deck) {
    Deck* deck = new Deck();
    Deck* pile = new Deck();
    Hand* h1 = new Hand();
    Hand* h2 = new Hand();

    populateDeck(*deck);

    ASSERT_EQ(deck->size(), 108);

    std::vector<std::unique_ptr<Player>> players;
    std::unique_ptr<Player> p1(new Player("Brandon", h1));
    std::unique_ptr<Player> p2(new Player("Mark", h2));

    players.push_back(std::move(p1));
    players.push_back(std::move(p2));

    {

        Match m(players, deck, pile);

        Card topCard = m.getDeck()->peekCard();

        m.drawCard(0);

        ASSERT_EQ(m.getDeck()->size(), 107);
        ASSERT_EQ(m.getPlayer(0)->getHand()->size(), 1);
        ASSERT_EQ(m.getPlayer(1)->getHand()->size(), 0);
        ASSERT_EQ(m.getPlayer(0)->getHand()->getCard(0), topCard);

        Card topCard2 = m.getDeck()->peekCard();

        m.drawCard(1);

        ASSERT_EQ(m.getDeck()->size(), 106);
        ASSERT_EQ(m.getPlayer(1)->getHand()->size(), 1);
        ASSERT_EQ(m.getPlayer(1)->getHand()->getCard(0), topCard2);
    }

    ASSERT_EQ(h1->size(), 0);
    ASSERT_EQ(h2->size(), 0);
}

TEST(match_tests, play_card_from_hand) {
    Deck* deck = new Deck();
    Deck* pile = new Deck();

    Hand* h1 = new Hand();
    Card c(CardColors::BLUE, CardValues::ONE, false);
    h1->addCard(c);

    std::vector<std::unique_ptr<Player>> players;
    std::unique_ptr<Player> p1(new Player("Brandon", h1));

    players.push_back(std::move(p1));

    Match m(players, deck, pile);

    m.playCard(0, 0);

    ASSERT_EQ(m.isWild(), false);
    ASSERT_EQ(m.getPile()->peekCard(), c);
    ASSERT_EQ(m.getPile()->size(), 1);
    ASSERT_EQ(m.getPlayer(0)->getHand()->size(), 0);

}

TEST(match_tests, play_wild_card_from_hand) {
    Deck* deck = new Deck();
    Deck* pile = new Deck();

    Hand* h1 = new Hand();
    Card c(CardColors::WILD, CardValues::WILD, true);
    h1->addCard(c);

    std::vector<std::unique_ptr<Player>> players;
    std::unique_ptr<Player> p1(new Player("Brandon", h1));

    players.push_back(std::move(p1));

    Match m(players, deck, pile);

    m.playCard(0, 0);

    ASSERT_EQ(m.isWild(), true);

    m.setWildColor(CardColors::YELLOW);
    Card newCard(CardColors::YELLOW, CardValues::WILD, false);

    ASSERT_EQ(m.isWild(), false);
    ASSERT_EQ(m.getPile()->peekCard(), newCard);
    ASSERT_EQ(m.getPile()->size(), 1);

}