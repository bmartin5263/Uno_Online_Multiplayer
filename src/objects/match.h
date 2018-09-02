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

    Match(std::vector<std::unique_ptr<Player>> & players, Deck* deck, Deck* pile);
//    Match(const Match &other);
//    Match& operator= (const Match &other);
    ~Match();

    void drawCard();
    void playCard(unsigned long cardIndex);
    void pass();
    void setWildColor(CardColors color);
    void setTurn(int turn);
    void pushFirstPileCard();

    // Accessors
    Deck* getDeck();
    Deck* getPile();
    std::vector<std::unique_ptr<Player>> const & getPlayers();
    Player* getPlayer(int playerId);
    int getTurn();
    bool isReversed();
    bool isComplete();
    bool isAborted();
    bool isWild();

private:

    void nextTurn();
    void resolveCard();
    void randomlyChangeTopColor();

    std::vector<std::unique_ptr<Player>> players;
    std::unique_ptr<Deck> deck;
    std::unique_ptr<Deck> pile;
    int turn;
    int consecutivePasses;
    bool reverse;
    bool complete;
    bool abort;

};

#endif //UNO_ONLINE_MULTIPLAYER_MATCH_H
