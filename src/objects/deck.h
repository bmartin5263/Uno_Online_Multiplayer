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
    std::vector<Card>::iterator begin();
    std::vector<Card>::iterator end();
    void pushCard(Card& card);
    unsigned long size();
    bool empty();

private:

    std::vector<Card> deck;

};

#endif //UNO_ONLINE_MULTIPLAYER_DECK_H
