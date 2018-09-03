//
// Created by Brandon Martin on 9/3/18.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../../src/objects/lobby.h"

using testing::Eq;

TEST(lobby_tests, create_lobby) {

    Lobby lobby;

    ASSERT_EQ(lobby.getPlayers().size(), 0);

}

TEST(lobby_tests, add_player) {

    Lobby lobby;

    Player* p = new Player("Brandon", new Hand());

    lobby.addPlayer(p);
    ASSERT_EQ(lobby.getPlayers().size(), 1);
    ASSERT_EQ(lobby.getPlayer(0)->getName(), "Brandon");
    ASSERT_EQ(lobby.getPlayer(0)->getPoints(), 0);

}

TEST(lobby_tests, remove_player) {

    Lobby lobby;

    Player* p = new Player("Brandon", new Hand());

    lobby.addPlayer(p);
    ASSERT_EQ(lobby.getPlayers().size(), 1);

    lobby.deletePlayer(0);
    ASSERT_EQ(lobby.getPlayers().size(), 0);

}

TEST(lobby_tests, try_to_add_more_than_four_players) {

    Lobby lobby;

    Player* p1 = new Player("Brandon", new Hand());
    Player* p2 = new Player("Frank", new Hand());
    Player* p3 = new Player("Mark", new Hand());
    Player* p4 = new Player("Jack", new Hand());
    Player* p5 = new Player("Anya", new Hand());

    lobby.addPlayer(p1);
    lobby.addPlayer(p2);
    lobby.addPlayer(p3);
    lobby.addPlayer(p4);
    ASSERT_EQ(lobby.getPlayers().size(), 4);

    try {
        lobby.addPlayer(p5);
        FAIL();
    } catch (std::overflow_error const & err) {

    }

    ASSERT_EQ(lobby.getPlayers().size(), 4);

}

TEST(lobby_tests, try_to_remove_zero_players) {

    Lobby lobby;
    ASSERT_EQ(lobby.getPlayers().size(), 0);

    try {
        lobby.deletePlayer(0);
        FAIL();
    } catch (std::underflow_error const & err) {

    }

    ASSERT_EQ(lobby.getPlayers().size(), 0);

}

TEST(lobby_tests, try_to_remove_invalid_player) {

    Lobby lobby;
    Player* p1 = new Player("Brandon", new Hand());
    lobby.addPlayer(p1);

    try {
        lobby.deletePlayer(1);
        FAIL();
    } catch (std::length_error const & err) {

    }

    ASSERT_EQ(lobby.getPlayers().size(), 1);

}