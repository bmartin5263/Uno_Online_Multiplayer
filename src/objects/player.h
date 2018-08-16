//
// Created by Brandon Martin on 8/12/18.
//

#ifndef UNO_ONLINE_MULTIPLAYER_PLAYER_H
#define UNO_ONLINE_MULTIPLAYER_PLAYER_H

#include <string>
#include "hand.h"

class Player {

public:

    Player(std::string name, Hand* hand);
    Player(const Player &other);
    Player& operator= (const Player &other);
    ~Player();

    void addPoints(int pts);
    int getPoints();
    std::string getName();
    std::shared_ptr<Hand> getHand();

private:

    std::string name;
    std::shared_ptr<Hand> hand;
    int points;

};

#endif //UNO_ONLINE_MULTIPLAYER_PLAYER_H
