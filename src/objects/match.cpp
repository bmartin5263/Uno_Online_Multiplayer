//
// Created by Brandon Martin on 8/15/18.
//

#include "match.h"

Match::Match(std::vector<std::unique_ptr<Player>> &players, Deck *deck, Deck *pile) :
    deck(deck), pile(pile), turn(0), consecutivePasses(0), complete(false), abort(false), reverse(false)
{
//    if (players.size() < MINIMUM_PLAYERS) {
//        throw std::length_error("Match initialized with less than two players");
//    }
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

unsigned int Match::getTurn() {
    return turn;
}

std::vector<std::unique_ptr<Player>> const & Match::getPlayers() {
    return players;
}

Player* Match::getPlayer(int playerId) {
    return players[playerId].get();
}

void Match::drawCard() {
    if (deck->size() == 0) {
        throw std::length_error("Cannot draw from an empty deck");
    }
    Card card = deck->popCard();
    players[turn]->getHand()->addCard(card);
    if (players[turn]->getForceDraws() > 0) {
        players[turn]->addForceDraws(-1);
    }
}

void Match::playCard(unsigned long cardIndex) {
    if (players[turn]->getForceDraws() > 0) {
        throw std::logic_error("Cannot Play A Card When You Must Draw");
    }
    Card peekCard = players[turn]->getHand()->getCard(cardIndex);
    Card topCard = pile->peekCard();
    if (peekCard.getValue() != topCard.getValue() && peekCard.getColor() != topCard.getColor()
        && !peekCard.isWild()) {
        throw std::logic_error("Cannot Play A Non-Wild Card That Doesn't Match The Pile's Color or Value");
    }
    Card card = players[turn]->getHand()->removeCard(cardIndex);
    pile->pushCard(card);
    consecutivePasses = 0; // reset passes
    resolveCard();
}

void Match::nextTurn() {
    unsigned int playersLen = (unsigned int)players.size();
    if (reverse) {
        if (turn == 0) {
            setTurn(playersLen - 1);
        } else {
            setTurn(turn - 1);
        }
    } else {
        if (turn == playersLen - 1) {
            setTurn((unsigned int)0);
        } else {
            setTurn(turn + 1);
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
    if (!topCard.isWild() && consecutivePasses != players.size()) {
        throw std::logic_error("Cannot change the color of a non-wild card");
    }
    Card newCard(color, topCard.getValue());
    pile->exchangeTopCard(newCard);
}

/*
 *  Testing function for force-setting the turn, should not be used in game logic, turns
 *  are automatically changed after playing the proper card.
 */
void Match::setTurn(unsigned int turn) {
    if (turn >= players.size()) {
        throw std::length_error("Turn number is greater than the number of players");
    }
    this->turn = turn;
}

/*
 *  Takes top card from the deck and adds it to the pile to start the game. Chooses random
 *  player for first turn
 */
void Match::start() {
    if (deck->size() < 1) {
        throw std::length_error("Illegal deck state, cannot start game with an empty deck");
    }
    if (pile->size() > 0) {
        throw std::logic_error("Illegal pile state, cannot start game with a non-empty pile");
    }
    Card card = deck->popCard();
    pile->pushCard(card);
    turn = (unsigned int)rand() % 4;
}

void Match::pass() {
    if (deck->size() > 0) {
        throw std::length_error("Cannot pass while deck is non-empty");
    }
    Card topCard = pile->peekCard();
    if (players[turn]->getHand()->hasPlayableCard(topCard.getColor(), topCard.getValue())) {
        throw std::logic_error("Cannot pass with a playable card");
    }
    consecutivePasses++;
    if (consecutivePasses == players.size()) {
        randomlyChangeTopColor();
        consecutivePasses = 0;
    }
}

void Match::randomlyChangeTopColor() {
    CardColors newColor;
    do {
        int val = rand() % 4;
        newColor = CARD_COLORS[val];
    } while (newColor == pile->peekCard().getColor());
    setWildColor(newColor);
}

Match::~Match() {
    // Nothing
}