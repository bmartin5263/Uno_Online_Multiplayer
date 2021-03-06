//
// Created by Brandon Martin on 8/12/18.
//

#include "player.h"

Player::Player(std::string name, Hand* hand) :
    name(name), hand(hand), points(0), forceDraw(0)
{
}

Player::Player(const Player &other) :
    name(other.name), hand(std::unique_ptr<Hand>(new Hand)), points(other.points), forceDraw(other.forceDraw)
{
    // Copy over hand contents
    for (auto it = other.hand->begin(); it != other.hand->end(); it++) {
        hand->addCard(*it);
    }
}

Player & Player::operator = (const Player &other)
{
    if (this != &other) {
        this->name = other.name;
        this->hand = std::unique_ptr<Hand>(new Hand);
        this->points = other.points;
        this->forceDraw = other.forceDraw;

        // Copy over hand contents
        for (auto it = other.hand->begin(); it != other.hand->end(); it++) {
            hand->addCard(*it);
        }
    }

    return *this;
}

void Player::addPoints(int pts) {
    points += pts;
}

Hand* Player::getHand() {
    return hand.get();
}

std::string Player::getName() {
    return name;
}

int Player::getPoints() {
    return points;
}

int Player::getForceDraws() {
    return forceDraw;
}

void Player::addForceDraws(int draws) {
    forceDraw += draws;
}

Player::~Player() {
    // nothing
}