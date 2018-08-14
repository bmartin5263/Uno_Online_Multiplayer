//
// Created by Brandon Martin on 8/12/18.
//

#ifndef UNO_ONLINE_MULTIPLAYER_HAND_H
#define UNO_ONLINE_MULTIPLAYER_HAND_H

#include <vector>
#include "card.h"

class Hand {

public:

    Hand();
    Hand(const Hand &other);
    Hand& operator = (const Hand & other);
    ~Hand();

    Card getCard(unsigned long index);
    Card removeCard(unsigned long index);

    void addCard(Card& card);

    std::vector<Card>::iterator begin();
    std::vector<Card>::iterator end();

    unsigned long size();
    bool empty();

private:

    std::vector<Card> hand;

};

#endif //UNO_ONLINE_MULTIPLAYER_HAND_H
