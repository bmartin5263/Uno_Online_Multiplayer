cmake_minimum_required(VERSION 3.10)
project(Uno_Online_Multiplayer)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "-lncurses -lpanel")

add_subdirectory(lib/googletest-release-1.8.0)
include_directories(lib/googletest-release-1.8.0/googletest/include)
include_directories(lib/googletest-release-1.8.0/googlemock/include)

add_executable(Uno_Online_Multiplayer src/main.cpp src/ui/ui.cpp src/ui/ui.h src/activities/mode_select.cpp src/activities/mode_select.h src/activities/lobby.cpp src/activities/lobby.h src/objects/card.cpp src/objects/card.h src/objects/deck.cpp src/objects/deck.h src/activities/activity.cpp src/activities/activity.h src/constants/constants.h tests/objects_tests/card_tests.cpp src/objects/hand.cpp src/objects/hand.h src/objects/player.cpp src/objects/player.h tests/objects_tests/deck_tests.cpp tests/objects_tests/hand_tests.cpp tests/objects_tests/player_tests.cpp tests/objects_tests/player_tests.h)

target_link_libraries(Uno_Online_Multiplayer gtest gtest_main)