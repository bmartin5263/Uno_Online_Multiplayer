//
// Created by Brandon Martin on 8/12/18.
//

#include "hand.h"

Hand::Hand()
{
}

Hand::Hand(const Hand &other) :
        hand(other.hand)
{
}

Hand & Hand::operator = (const Hand& other)
{
    if (this != &other) {
        this->hand = other.hand;
    }

    return *this;
}

void Hand::addCard(Card& card) {
    hand.push_back(card);
}

Card Hand::getCard(unsigned long index) {
    if (index >= hand.size()) {
        throw std::out_of_range("Card index out of range of hand");
    }
    return hand[index];
}

Card Hand::removeCard(unsigned long index) {
    if (index >= hand.size()) {
        throw std::out_of_range("Card index out of range of hand");
    }
    Card card = hand.at(index);
    hand.erase(hand.begin()+index);
    return card;
}

unsigned long Hand::size() {
    return hand.size();
}

bool Hand::empty() {
    return hand.empty();
}

std::vector<Card>::iterator Hand::begin() {
    return hand.begin();
}

std::vector<Card>::iterator Hand::end() {
    return hand.end();
}

Hand::~Hand() {
    // Do Nothing
}