//
// Created by Brandon Martin on 8/12/18.
//

#include "player.h"

Player::Player(std::string name, std::shared_ptr<Hand> hand) :
    name(name), hand(hand), points(0)
{
}

Player::Player(const Player &other) :
    name(other.name), hand(other.hand), points(other.points)
{
}

Player & Player::operator = (const Player &other)
{
    if (this != &other) {
        this->name = other.name;
        this->hand = other.hand;
        this->points = other.points;
    }

    return *this;
}

void Player::addPoints(int pts) {
    points += pts;
}

std::shared_ptr<Hand> Player::getHand() {
    return hand;
}

std::string Player::getName() {
    return name;
}

int Player::getPoints() {
    return points;
}

Player::~Player() {
    // nothing
}