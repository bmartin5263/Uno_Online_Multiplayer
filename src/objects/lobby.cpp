//
// Created by Brandon Martin on 9/2/18.
//

#include "lobby.h"

Lobby::Lobby()
{
}

void Lobby::addPlayer(Player *p) {
    if (players.size() >= MAXIMUM_PLAYERS) {
        throw std::overflow_error("Maximum player limit reached");
    }
    std::unique_ptr<Player> player = std::unique_ptr<Player>(p);
    players.push_back(std::move(player));
}

void Lobby::deletePlayer(int playerId) {
    if (players.size() <= 0) {
        throw std::underflow_error("Lobby doesn't have any Players");
    }
    if (playerId >= players.size()) {
        throw std::length_error("Invalid playerId to delete from Lobby");
    }
    players.erase(players.begin() + playerId);
}

Player* Lobby::getPlayer(int playerId) {
    if (playerId >= players.size()) {
        throw std::length_error("Invalid playerId for Lobby");
    }
    return players[playerId].get();
}

std::vector<std::unique_ptr<Player>> const & Lobby::getPlayers() {
    return players;
}

Lobby::~Lobby()
{
}