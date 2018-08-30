//
// Created by Brandon Martin on 8/15/18.
//

#include "match.h"

Match::Match(std::vector<Player> players, std::shared_ptr<Deck> deck, std::shared_ptr<Deck> pile) :
    players(players), deck(deck), pile(pile)
{
}

std::shared_ptr<Deck> Match::getDeck() {
    return deck;
}

std::shared_ptr<Deck> Match::getPile() {
    return pile;
}

std::vector<Player> Match::getPlayers() {
    return players;
}

void Match::drawCard(int playerId) {
    Card card = deck->popCard();
    players[playerId].getHand()->addCard(card);
}

void Match::playCard(int playerId, unsigned long cardIndex) {
    Card card = players[playerId].getHand()->removeCard(cardIndex);
    pile->pushCard(card);
}

void Match::nextTurn() {
    unsigned long playersLen = players.size();
    if (reverse) {
        if (turn == 0) {
            turn = (int)playersLen - 1;
        } else {
            turn -= 1;
        }
    } else {
        if (turn == playersLen - 1) {
            turn = 0;
        } else {
            turn += 1;
        }
    }
}

void Match::resolveCard() {
    Card card = pile->peekCard();
}