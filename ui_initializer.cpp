//
// Created by Brandon Martin on 6/15/18.
//

/*
 * This file contains all the initializing information for the UI
 */

#include "ui.h"

UI::UI()
{
    initializeCurses();
    initializeElements();
}

void UI::initializeCurses()
{
    // Buckle up...
    // Standard Curses Setup with Custom Colors
    printf("\e[8;33;70t");  // Resize Terminal to 33 Rows and 70 Cols
    initscr();
    start_color();
    curs_set(0);
    init_pair(1, 15, COLOR_BLACK);
    init_pair(2, 39, COLOR_BLACK);
    init_pair(3, 199, COLOR_BLACK);
    init_pair(4, 82, COLOR_BLACK);
    init_pair(5, 226, COLOR_BLACK);
    init_pair(6, COLOR_BLACK, 15);
    init_pair(7, 39, 17);
    init_pair(8, 199, 52);
    init_pair(9, 82, 22);
    init_pair(10, 226, 58);
    init_pair(11, 8, COLOR_BLACK);
    cbreak();
    keypad(stdscr, TRUE);
    noecho();

    // Define Text Colors
    TEXT_COLORS[Colors::WHITE] = COLOR_PAIR(1);
    TEXT_COLORS[Colors::BLUE] = COLOR_PAIR(2);
    TEXT_COLORS[Colors::RED] = COLOR_PAIR(3);
    TEXT_COLORS[Colors::GREEN] = COLOR_PAIR(4);
    TEXT_COLORS[Colors::YELLOW] = COLOR_PAIR(5);
    TEXT_COLORS[Colors::INVERT] = COLOR_PAIR(6);
    TEXT_COLORS[Colors::GRAY] = COLOR_PAIR(11);

    box(stdscr, 0, 0);      // Create a Box around the entire Terminal
    refresh();
}

void UI::initializeElements()
{
    // Create Elements with Default Values
    // Its pretty ugly...

    // Element(xPos, yPos, xDim, yDim, color, borderType, parent/tether)

    el[Elements::TITLE] = new Element(0, 0, 70, 7, TEXT_COLORS[Colors::WHITE], Borders::TITLE, nullptr);

    el[Elements::WINDOW_MODE] = new Element(17, 7, 36, 21, TEXT_COLORS[Colors::WHITE], Borders::BOX, nullptr);
    el[Elements::MAIN_STAGE] = new Element(1, 1, 34, 4, TEXT_COLORS[Colors::BLUE], Borders::BOX, el[Elements::WINDOW_MODE]);
    el[Elements::BUTTON_LOCAL] = new Element(1, 8, 34, 3, TEXT_COLORS[Colors::WHITE], Borders::BOX, el[Elements::WINDOW_MODE]);
    el[Elements::BUTTON_HOST] = new Element(1, 11, 34, 3, TEXT_COLORS[Colors::WHITE], Borders::BOX, el[Elements::WINDOW_MODE]);
    el[Elements::BUTTON_JOIN] = new Element(1, 14, 34, 3, TEXT_COLORS[Colors::WHITE], Borders::BOX, el[Elements::WINDOW_MODE]);
    el[Elements::BUTTON_EXIT] = new Element(1, 17, 34, 3, TEXT_COLORS[Colors::WHITE], Borders::BOX, el[Elements::WINDOW_MODE]);

    el[Elements::WINDOW_LOBBY] = new Element(0, 6, 70, 26, TEXT_COLORS[Colors::WHITE], Borders::MIDDLE, nullptr);
    el[Elements::PLAYER_STAGE_0] = new Element(1, 1, 34, 4, TEXT_COLORS[Colors::BLUE], Borders::BOX, el[Elements::WINDOW_LOBBY]);
    el[Elements::PLAYER_STAGE_1] = new Element(35, 1, 34, 4, TEXT_COLORS[Colors::RED], Borders::BOX, el[Elements::WINDOW_LOBBY]);
    el[Elements::PLAYER_STAGE_2] = new Element(1, 5, 34, 4, TEXT_COLORS[Colors::GREEN], Borders::BOX, el[Elements::WINDOW_LOBBY]);
    el[Elements::PLAYER_STAGE_3] = new Element(35, 5, 34, 4, TEXT_COLORS[Colors::YELLOW], Borders::BOX, el[Elements::WINDOW_LOBBY]);
    el[Elements::BUTTON_START] = new Element(1, 10, 34, 3, TEXT_COLORS[Colors::BLUE], Borders::BOX, el[Elements::WINDOW_LOBBY]);
    el[Elements::BUTTON_ADD_AI] = new Element(1, 13, 17, 3, TEXT_COLORS[Colors::WHITE], Borders::BOX, el[Elements::WINDOW_LOBBY]);
    el[Elements::BUTTON_SEARCH] = new Element(18, 13, 17, 3, TEXT_COLORS[Colors::WHITE], Borders::BOX, el[Elements::WINDOW_LOBBY]);
    el[Elements::BUTTON_KICK] = new Element(1, 16, 34, 3, TEXT_COLORS[Colors::WHITE], Borders::BOX, el[Elements::WINDOW_LOBBY]);
    el[Elements::BUTTON_CLOSE] = new Element(1, 19, 34, 3, TEXT_COLORS[Colors::WHITE], Borders::BOX, el[Elements::WINDOW_LOBBY]);
    el[Elements::BUTTON_SETTINGS] = new Element(1, 22, 34, 3, TEXT_COLORS[Colors::WHITE], Borders::BOX, el[Elements::WINDOW_LOBBY]);

    el[Elements::WINDOW_SETTINGS] = new Element(35, 16, 34, 15, TEXT_COLORS[Colors::WHITE], Borders::BOX, nullptr);
    el[Elements::BUTTON_DISPLAY_EFFECTS] = new Element(1, 3, 32, 1, TEXT_COLORS[Colors::RED], Borders::NONE, el[Elements::WINDOW_SETTINGS]);
    el[Elements::BUTTON_COMPUTER_SPEED] = new Element(1, 6, 32, 1, TEXT_COLORS[Colors::WHITE], Borders::NONE, el[Elements::WINDOW_SETTINGS]);
    el[Elements::BUTTON_SHOW_HANDS] = new Element(1, 9, 32, 1, TEXT_COLORS[Colors::WHITE], Borders::NONE, el[Elements::WINDOW_SETTINGS]);
    el[Elements::BUTTON_DOES_NOTHING] = new Element(1, 12, 32, 1, TEXT_COLORS[Colors::WHITE], Borders::NONE, el[Elements::WINDOW_SETTINGS]);

    el[Elements::WINDOW_MATCH] = new Element(0, 6, 70, 18, TEXT_COLORS[Colors::WHITE], Borders::MATCH, nullptr);
    el[Elements::WINDOW_HAND] = new Element(0, 23, 70, 9, TEXT_COLORS[Colors::WHITE], Borders::MIDDLE, nullptr);
    el[Elements::PREV_CARD] = new Element(2, 4, 4, 4, TEXT_COLORS[Colors::WHITE], Borders::BOX, el[Elements::WINDOW_HAND]);
    el[Elements::CARD_0] = new Element(7, 4, 4, 4, TEXT_COLORS[Colors::WHITE], Borders::BOX, el[Elements::WINDOW_HAND]);
    el[Elements::CARD_1] = new Element(11, 4, 4, 4, TEXT_COLORS[Colors::WHITE], Borders::BOX, el[Elements::WINDOW_HAND]);
    el[Elements::CARD_2] = new Element(15, 4, 4, 4, TEXT_COLORS[Colors::WHITE], Borders::BOX, el[Elements::WINDOW_HAND]);
    el[Elements::CARD_3] = new Element(19, 4, 4, 4, TEXT_COLORS[Colors::WHITE], Borders::BOX, el[Elements::WINDOW_HAND]);
    el[Elements::CARD_4] = new Element(23, 4, 4, 4, TEXT_COLORS[Colors::WHITE], Borders::BOX, el[Elements::WINDOW_HAND]);
    el[Elements::CARD_5] = new Element(27, 4, 4, 4, TEXT_COLORS[Colors::WHITE], Borders::BOX, el[Elements::WINDOW_HAND]);
    el[Elements::CARD_6] = new Element(31, 4, 4, 4, TEXT_COLORS[Colors::WHITE], Borders::BOX, el[Elements::WINDOW_HAND]);
    el[Elements::CARD_7] = new Element(35, 4, 4, 4, TEXT_COLORS[Colors::WHITE], Borders::BOX, el[Elements::WINDOW_HAND]);
    el[Elements::CARD_8] = new Element(39, 4, 4, 4, TEXT_COLORS[Colors::WHITE], Borders::BOX, el[Elements::WINDOW_HAND]);
    el[Elements::CARD_9] = new Element(43, 4, 4, 4, TEXT_COLORS[Colors::WHITE], Borders::BOX, el[Elements::WINDOW_HAND]);
    el[Elements::CARD_10] = new Element(47, 4, 4, 4, TEXT_COLORS[Colors::WHITE], Borders::BOX, el[Elements::WINDOW_HAND]);
    el[Elements::CARD_11] = new Element(51, 4, 4, 4, TEXT_COLORS[Colors::WHITE], Borders::BOX, el[Elements::WINDOW_HAND]);
    el[Elements::CARD_12] = new Element(55, 4, 4, 4, TEXT_COLORS[Colors::WHITE], Borders::BOX, el[Elements::WINDOW_HAND]);
    el[Elements::CARD_13] = new Element(59, 4, 4, 4, TEXT_COLORS[Colors::WHITE], Borders::BOX, el[Elements::WINDOW_HAND]);
    el[Elements::NEXT_CARD] = new Element(64, 4, 4, 4, TEXT_COLORS[Colors::WHITE], Borders::BOX, el[Elements::WINDOW_HAND]);

    el[Elements::DECK_METER] = new Element(2, 5, 5, 11, TEXT_COLORS[Colors::WHITE], Borders::BOX, el[Elements::WINDOW_MATCH]);
    el[Elements::DECK_COUNT] = new Element(1, 2, 9, 2, TEXT_COLORS[Colors::WHITE], Borders::NONE, el[Elements::WINDOW_MATCH]);
    el[Elements::BELOW_CARD] = new Element(27, 2, 14, 12, TEXT_COLORS[Colors::WHITE], Borders::BOX, el[Elements::WINDOW_MATCH]);
    el[Elements::TOP_CARD] = new Element(29, 4, 14, 12, TEXT_COLORS[Colors::WHITE], Borders::BOX, el[Elements::WINDOW_MATCH]);
    el[Elements::PLAYER_TILE_0] = new Element(55, 1, 14, 4, TEXT_COLORS[Colors::BLUE], Borders::BOX, el[Elements::WINDOW_MATCH]);
    el[Elements::PLAYER_TILE_1] = new Element(55, 5, 14, 4, TEXT_COLORS[Colors::RED], Borders::BOX, el[Elements::WINDOW_MATCH]);
    el[Elements::PLAYER_TILE_2] = new Element(55, 9, 14, 4, TEXT_COLORS[Colors::GREEN], Borders::BOX, el[Elements::WINDOW_MATCH]);
    el[Elements::PLAYER_TILE_3] = new Element(55, 13, 14, 4, TEXT_COLORS[Colors::YELLOW], Borders::BOX, el[Elements::WINDOW_MATCH]);

    // Draw Text Onto Elements

    putText(Elements::TITLE, 25, 1, "|| ||", Colors::BLUE);
    putText(Elements::TITLE, 31, 1, "||\\ ||", Colors::GREEN);
    putText(Elements::TITLE, 39, 1, "// \\\\", Colors::RED);
    putText(Elements::TITLE, 25, 2, "|| ||", Colors::BLUE);
    putText(Elements::TITLE, 31, 2, "||\\\\||", Colors::GREEN);
    putText(Elements::TITLE, 38, 2, "((   ))", Colors::RED);
    putText(Elements::TITLE, 25, 3, "\\\\ //", Colors::BLUE);
    putText(Elements::TITLE, 31, 3, "|| \\||", Colors::GREEN);
    putText(Elements::TITLE, 39, 3, "\\\\ //", Colors::RED);
    putText(Elements::NEXT_CARD, 1, 1, "->", Colors::WHITE);
    putText(Elements::NEXT_CARD, 1, 2, "->", Colors::WHITE);
    putText(Elements::PREV_CARD, 1, 1, "<-", Colors::WHITE);
    putText(Elements::PREV_CARD, 1, 2, "<-", Colors::WHITE);
    putText(Elements::DECK_COUNT, 0, 0, "Deck:", Colors::WHITE);
    putText(Elements::DECK_COUNT, 0, 1, "0 Cards", Colors::WHITE);
    putText(Elements::WINDOW_SETTINGS, 13, 1, "Settings", Colors::WHITE);

    // Make some Lines and Borders
    putSpecialChar(Elements::TITLE, 0, 4, ACS_LTEE, Colors::WHITE);
    putSpecialChar(Elements::TITLE, 69, 4, ACS_RTEE, Colors::WHITE);
    putSpecialChar(Elements::WINDOW_LOBBY, 0, 9, ACS_LTEE, Colors::WHITE);
    putSpecialChar(Elements::WINDOW_LOBBY, 69, 9, ACS_RTEE, Colors::WHITE);
    putSpecialChar(Elements::WINDOW_HAND, 0, 2, ACS_LTEE, Colors::WHITE);
    putSpecialChar(Elements::WINDOW_HAND, 69, 2, ACS_RTEE, Colors::WHITE);
    putSpecialChar(Elements::WINDOW_MODE, 0, 5, ACS_LTEE, Colors::WHITE);
    putSpecialChar(Elements::WINDOW_MODE, 0, 7, ACS_LTEE, Colors::WHITE);
    putSpecialChar(Elements::WINDOW_MODE, 35, 5, ACS_RTEE, Colors::WHITE);
    putSpecialChar(Elements::WINDOW_MODE, 35, 7, ACS_RTEE, Colors::WHITE);
    putSpecialChar(Elements::WINDOW_SETTINGS, 33, 2, ACS_RTEE, Colors::WHITE);
    putSpecialChar(Elements::WINDOW_SETTINGS, 0, 2, ACS_LTEE, Colors::WHITE);
    for (int i = 1 ; i < 69; i++) {
        putSpecialChar(Elements::TITLE, i, 4, ACS_HLINE, Colors::WHITE);
        putSpecialChar(Elements::WINDOW_LOBBY, i, 9, ACS_HLINE, Colors::WHITE);
        putSpecialChar(Elements::WINDOW_HAND, i, 2, ACS_HLINE, Colors::WHITE);
        if (i < 35) {
            putSpecialChar(Elements::WINDOW_MODE, i, 5, ACS_HLINE, Colors::WHITE);
            putSpecialChar(Elements::WINDOW_MODE, i, 7, ACS_HLINE, Colors::WHITE);
            if (i < 33) putSpecialChar(Elements::WINDOW_SETTINGS, i, 2, ACS_HLINE, Colors::WHITE);
        }
    }

    // Initialize Button Text
    int updateSize = 14;
    ButtonUpdate data[14] = {
            ButtonUpdate(Elements::BUTTON_START, 11, 32, "Start Game", false, Colors::DEFAULT, false),
            ButtonUpdate(Elements::BUTTON_ADD_AI, 5, 15, "Add AI", false, Colors::DEFAULT, false),
            ButtonUpdate(Elements::BUTTON_SEARCH, 4, 15, "Search", false, Colors::DEFAULT, false),
            ButtonUpdate(Elements::BUTTON_KICK, 11, 32, "Kick Player", false, Colors::DEFAULT, false),
            ButtonUpdate(Elements::BUTTON_CLOSE, 11, 32, "Close Room", false, Colors::DEFAULT, false),
            ButtonUpdate(Elements::BUTTON_SETTINGS, 12, 32, "Settings", false, Colors::DEFAULT, false),
            ButtonUpdate(Elements::BUTTON_HOST, 8, 32, "Host Multiplayer", false, Colors::DEFAULT, false),
            ButtonUpdate(Elements::BUTTON_JOIN, 8, 32, "Join Multiplayer", false, Colors::DEFAULT, false),
            ButtonUpdate(Elements::BUTTON_LOCAL, 7, 32, "Local Singleplayer", false, Colors::DEFAULT, false),
            ButtonUpdate(Elements::BUTTON_EXIT, 14, 32, "Exit", false, Colors::DEFAULT, false),
            ButtonUpdate(Elements::BUTTON_DISPLAY_EFFECTS, 0, 32, "- Display Effects", false, Colors::DEFAULT, true),
            ButtonUpdate(Elements::BUTTON_COMPUTER_SPEED, 0, 32, "- Computer Speed", false, Colors::DEFAULT, true),
            ButtonUpdate(Elements::BUTTON_SHOW_HANDS, 0, 32, "- Show Computer Hands", false, Colors::DEFAULT, true),
            ButtonUpdate(Elements::BUTTON_DOES_NOTHING, 0, 32, "- Does Nothing", false, Colors::DEFAULT, true),
    };
    updateButtons(data, updateSize);


    // Finally, Hide Everything Except stdscr
    for (auto it=el.begin(); it!=el.end(); it++)
        if (it->first != Elements::MAIN)
            hide_panel(it->second->panel);
    updatePanels();
}


UI::~UI()
{
    // Delete all the elements
    for (auto it=el.begin(); it!=el.end(); it++)
        delete it->second;

    // End Curses
    endwin();
}