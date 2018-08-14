//
// Created by Brandon Martin on 8/12/18.
//

#include "card.h"

/*
 *  Returns associated point value for a card. Point values are set according to Uno rules
 */
int Card::getPointValue(const Card &card) {
    switch (card.getValue()) {
        case CardValues::ZERO:
            return 0;
        case CardValues::ONE:
            return 1;
        case CardValues::TWO:
            return 2;
        case CardValues::THREE:
            return 3;
        case CardValues::FOUR:
            return 4;
        case CardValues::FIVE:
            return 5;
        case CardValues::SIX:
            return 6;
        case CardValues::SEVEN:
            return 7;
        case CardValues::EIGHT:
            return 8;
        case CardValues::NINE:
            return 9;
        case CardValues::WILD:
        case CardValues::PLUS4:
            return 50;
        default:                    // skip, reverse, plus2
            return 20;
    }
}

Card::Card(CardColors color, CardValues value, bool wild) :
    color(color), value(value), wild(wild)
{
}

Card::Card(const Card &other) :
    color(other.color), value(other.value), wild(other.wild)
{
}

Card & Card::operator = (const Card &other)
{
    if (this != &other) {
        this->color = other.color;
        this->value = other.value;
        this->wild = other.wild;
    }

    return *this;
}

bool Card::isWild() const {
    return wild;
}

CardValues Card::getValue() const {
    return value;
}

CardColors Card::getColor() const {
    return color;
}

Card::~Card() {
    // Do Nothing
}