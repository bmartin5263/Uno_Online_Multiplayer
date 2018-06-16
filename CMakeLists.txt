cmake_minimum_required(VERSION 3.10)
project(Uno_Online_Multiplayer)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "-lncurses -lpanel")

add_executable(Uno_Online_Multiplayer main.cpp ui.cpp ui.h ui_initializer.cpp)