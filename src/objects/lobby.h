//
// Created by Brandon Martin on 9/2/18.
//

#ifndef UNO_ONLINE_MULTIPLAYER_LOBBY_H
#define UNO_ONLINE_MULTIPLAYER_LOBBY_H

#include "player.h"

class Lobby {

public:

    Lobby();
    ~Lobby();

    void addPlayer(Player* p);
    void deletePlayer(int playerId);
    std::vector<std::unique_ptr<Player>> const & getPlayers();
    Player* getPlayer(int playerId);

private:

    std::vector<std::unique_ptr<Player>> players;

};

#endif //UNO_ONLINE_MULTIPLAYER_LOBBY_H
