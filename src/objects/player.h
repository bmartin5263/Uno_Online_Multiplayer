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
    void addForceDraws(int draws);
    int getPoints();
    int getForceDraws();
    std::string getName();
    Hand* getHand();

private:

    std::string name;
    std::unique_ptr<Hand> hand;
    int points;
    int forceDraw;

};

#endif //UNO_ONLINE_MULTIPLAYER_PLAYER_H
