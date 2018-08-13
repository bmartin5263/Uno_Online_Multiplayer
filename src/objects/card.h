//
// Created by Brandon Martin on 8/12/18.
//

#ifndef UNO_ONLINE_MULTIPLAYER_CARD_H
#define UNO_ONLINE_MULTIPLAYER_CARD_H

#include "../constants/constants.h"

class Card {

public:

    static int getPointValue(const Card& card);

    Card(CardColors color, CardValues value, bool wild);
    Card(const Card &other) = delete;
    Card& operator = (const Card & other) = delete;
    ~Card();

    CardColors getColor() const;
    CardValues getValue() const;
    bool isWild() const;

private:

    const CardColors color;
    const CardValues value;
    const bool wild;

};

#endif //UNO_ONLINE_MULTIPLAYER_CARD_H
