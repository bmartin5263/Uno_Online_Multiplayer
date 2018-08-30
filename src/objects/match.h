//
// Created by Brandon Martin on 8/15/18.
//

#ifndef UNO_ONLINE_MULTIPLAYER_MATCH_H
#define UNO_ONLINE_MULTIPLAYER_MATCH_H

#include <vector>
#include "deck.h"
#include "player.h"

/*
 * Match is the master object that holds the Uno match's state and all the methods to operate on that state.
 * For network games, the host program keeps track of the match state for all players and sends to each player
 * a stripped down state containing all information pertinent to that player (see MatchState).
 */

class Match {

public:

    Match(std::vector<Player> players, std::shared_ptr<Deck> deck, std::shared_ptr<Deck> pile);
    //~Match();

    void drawCard(int playerId);
    void playCard(int playerId, unsigned long cardIndex);

    std::shared_ptr<Deck> getDeck();
    std::shared_ptr<Deck> getPile();
    std::vector<Player> getPlayers();

private:

    void nextTurn();
    void resolveCard();

    std::vector<Player> players;
    std::shared_ptr<Deck> deck;
    std::shared_ptr<Deck> pile;
    int turn;
    bool reverse;
    bool complete;
    bool abort;

};

#endif //UNO_ONLINE_MULTIPLAYER_MATCH_H
