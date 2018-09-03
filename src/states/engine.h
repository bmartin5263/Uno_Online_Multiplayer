//
// Created by Brandon Martin on 9/2/18.
//

#ifndef UNO_ONLINE_MULTIPLAYER_ENGINE_H
#define UNO_ONLINE_MULTIPLAYER_ENGINE_H

#include <vector>

class GameState;

class Engine {

public:

    void changeState(GameState* state);
    void pushState(GameState* state);
    void popState();

    void getInput();
    void update();
    void draw();

    bool running();
    void abort();

private:

    std::vector<std::unique_ptr<GameState>> states;
    bool runnning;

};

#endif //UNO_ONLINE_MULTIPLAYER_ENGINE_H
