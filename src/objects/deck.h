//
// Created by Brandon Martin on 8/12/18.
//

#ifndef UNO_ONLINE_MULTIPLAYER_DECK_H
#define UNO_ONLINE_MULTIPLAYER_DECK_H

#include <vector>
#include "card.h"

class Deck {

public:

    Deck();
    Deck(const Deck &other);
    Deck& operator = (const Deck & other);
    ~Deck();

    Card popCard();
    Card peekCard();
    void pushCard(Card& card);
    void exchangeTopCard(Card& card);
    unsigned long size();
    bool empty();

private:

    std::vector<Card> deck;

};

#endif //UNO_ONLINE_MULTIPLAYER_DECK_H
