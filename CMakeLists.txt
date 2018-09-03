cmake_minimum_required(VERSION 3.10)
project(Uno_Online_Multiplayer)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "-lncurses -lpanel")

add_subdirectory(lib/googletest-release-1.8.0)
include_directories(lib/googletest-release-1.8.0/googletest/include)
include_directories(lib/googletest-release-1.8.0/googlemock/include)
include_directories(lib/)

add_executable(Uno_Online_Multiplayer src/main.cpp src/ui/ui.cpp src/ui/ui.h src/states/mode_select.cpp src/states/mode_select.h src/states/match_lobby.cpp src/states/match_lobby.h src/objects/card.cpp src/objects/card.h src/objects/deck.cpp src/objects/deck.h src/states/game_state.cpp src/states/game_state.h src/constants/constants.h tests/objects_tests/card_tests.cpp src/objects/hand.cpp src/objects/hand.h src/objects/player.cpp src/objects/player.h tests/objects_tests/deck_tests.cpp tests/objects_tests/hand_tests.cpp tests/objects_tests/player_tests.cpp tests/objects_tests/match_tests.cpp src/objects/match.cpp src/objects/match.h src/objects/match_state.cpp src/objects/match_state.h src/states/engine.cpp src/states/engine.h src/ui/abstract_ui.cpp src/ui/abstract_ui.h src/ui/debug_ui.cpp src/ui/debug_ui.h src/states/play_match.cpp src/states/play_match.h src/objects/lobby.cpp src/objects/lobby.h tests/objects_tests/lobby_tests.cpp)

target_link_libraries(Uno_Online_Multiplayer gtest gtest_main)