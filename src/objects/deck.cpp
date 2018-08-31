//
// Created by Brandon Martin on 8/12/18.
//

#include "deck.h"

Deck::Deck()
{
}

Deck::Deck(const Deck &other) :
    deck(other.deck)
{
}

Deck & Deck::operator = (const Deck &other)
{
    if (this != &other) {
        this->deck = other.deck;
    }

    return *this;
}

void Deck::pushCard(Card& card) {
    deck.push_back(card);
}

Card Deck::popCard() {
    if (empty()) {
        throw std::underflow_error("Deck Underflow");
    }
    Card card = deck.back();
    deck.pop_back();
    return card;
}

Card Deck::peekCard() {
    if (empty()) {
        throw std::underflow_error("Deck Underflow");
    }
    return deck.back();
}

unsigned long Deck::size() {
    return deck.size();
}

bool Deck::empty() {
    return deck.empty();
}

std::vector<Card>::iterator Deck::begin() {
    return deck.begin();
}

std::vector<Card>::iterator Deck::end() {
    return deck.end();
}

/*
 * Change the Card at the top of the stack. For use with wild color changes.
 */
void Deck::exchangeTopCard(Card &card) {
    deck[0] = card;
}

Deck::~Deck() {
    // Nothing Here
}