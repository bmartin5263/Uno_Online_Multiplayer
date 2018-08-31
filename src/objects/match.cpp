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
    resolveCard();
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
    int draws = 0;
    bool forceDraw = false;
    switch (card.getValue()) {
        case CardValues::PLUS4:
            draws += 2;
        case CardValues::PLUS2:
            draws += 2;
            forceDraw = true;
            break;
        case CardValues::REVERSE:
            if (players.size() != 2) {
                reverse = not reverse;
                break;
            }
        case CardValues::SKIP:
            nextTurn();
            break;
        default:
            break;
    }
    nextTurn();
    if (forceDraw) {
        players[turn]->addForceDraws(draws);
    }
}

bool Match::isWild() {
    return pile->peekCard().isWild();
}

void Match::setWildColor(CardColors color) {
    Card topCard = pile->peekCard();
    Card newCard(color, topCard.getValue(), false);
    pile->exchangeTopCard(newCard);
}

void Match::setTurn(int turn) {
    this->turn = turn;
}

Match::~Match() {
    // Nothing
}