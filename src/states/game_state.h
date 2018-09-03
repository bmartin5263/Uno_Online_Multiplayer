//
// Created by Brandon Martin on 8/12/18.
//

#ifndef UNO_ONLINE_MULTIPLAYER_ACTIVITY_H
#define UNO_ONLINE_MULTIPLAYER_ACTIVITY_H

#include "engine.h"

class GameState {

public:

    GameState();
    ~GameState();

    virtual void getInput(Engine* engine) = 0;
    virtual void update(Engine* engine) = 0;
    virtual void draw(Engine* engine) = 0;
    virtual bool hasEvent() = 0;

};

#endif //UNO_ONLINE_MULTIPLAYER_ACTIVITY_H
