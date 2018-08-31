//
// Created by Brandon Martin on 8/15/18.
//

#include "match.h"

Match::Match(std::vector<std::unique_ptr<Player>> &players, Deck *deck, Deck *pile) :
    deck(deck), pile(pile), turn(0), complete(false), abort(false), reverse(false)
{
    for (auto it = players.begin(); it != players.end(); it++) {
        Player* x = it->get();
        this->players.push_back(std::unique_ptr<Player>(new Player(*x)));
    }
}

Deck* Match::getDeck() {
    return deck.get();
}

Deck* Match::getPile() {
    return pile.get();
}

bool Match::isAborted() {
    return abort;
}

bool Match::isComplete() {
    return complete;
}

bool Match::isReversed() {
    return reverse;
}

int Match::getTurn() {
    return turn;
}

std::vector<std::unique_ptr<Player>> const & Match::getPlayers() {
    return players;
}

Player* Match::getPlayer(int playerId) {
    return players[playerId].get();
}

void Match::drawCard(int playerId) {
    Card card = deck->popCard();
    players[playerId]->getHand()->addCard(card);
}

void Match::playCard(int playerId, unsigned long cardIndex) {
    Card card = players[playerId]->getHand()->removeCard(cardIndex);
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

Match::~Match() {
    // Nothing
}