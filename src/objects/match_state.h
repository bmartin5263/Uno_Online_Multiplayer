//
// Created by Brandon Martin on 8/29/18.
//

#ifndef UNO_ONLINE_MULTIPLAYER_MATCH_STATE_H
#define UNO_ONLINE_MULTIPLAYER_MATCH_STATE_H

#include "match.h"

class MatchState {

public:

    MatchState(Match& match, unsigned long playerId);
    ~MatchState();

    int playerId;
    int turn;
    int numberOfPlayers;
    int player1Cards;
    int player2Cards;
    int player3Cards;
    int player4Cards;
    // Might be used for player disconnects, ie 0 = normal, 1 = empty, 2 = disconnected, etc
    int player1Status;
    int player2Status;
    int player3Status;
    int player4Status;
    int handLength;
    Hand hand;
    Card topCard;
    Card belowCard;

private:

};

#endif //UNO_ONLINE_MULTIPLAYER_MATCH_STATE_H
