//
// Created by Brandon Martin on 6/15/18.
//

/*
 * This file contains all the initializing information for the UI
 */

#include "ui.h"

/* First We Will Initialize Canvases */

Canvas::Canvas(int x, int y, int cols, int rows, unsigned int colorPair, Borders border) :
    x(x), y(y), cols(cols), rows(rows), defaultColor(colorPair)
{
    // The literal canvas
    window = newwin(rows, cols, y, x);
    panel = new_panel(window);

    // Give it a basic border, if needed
    if (border != Borders::NONE)
        box(window, 0, 0);

    // Adjust the border based on position
    switch (border) {
        case Borders::TOP:
            mvwaddch(window, rows-1, 0, ACS_LTEE);
            mvwaddch(window, rows-1, cols-1, ACS_RTEE);
            break;
        case Borders::BOTTOM:
            mvwaddch(window, 0, 0, ACS_LTEE);
            mvwaddch(window, 0, cols-1, ACS_RTEE);
            break;
        case Borders::MIDDLE:
            mvwaddch(window, 0, 0, ACS_LTEE);
            mvwaddch(window, 0, cols-1, ACS_RTEE);
            mvwaddch(window, rows-1, 0, ACS_LTEE);
            mvwaddch(window, rows-1, cols-1, ACS_RTEE);
            break;
        case Borders::NONE:
        case Borders::FLOAT:        // Just a box, does not connect to another
            break;
    }

    wbkgd(window, defaultColor);
    wnoutrefresh(window);
}

// Bake a row onto the window. Cannot change.
void Canvas::drawRow(int y) {
    mvwaddch(window, y, 0, ACS_LTEE);
    mvwaddch(window, y, cols-1, ACS_RTEE);
    for (int i = 1 ; i < cols-1 ; i++) {
        mvwaddch(window, y, i, ACS_HLINE);
    }
    wnoutrefresh(window);
}

// Bake a box onto the window. Cannot change.
void Canvas::drawBox(int x, int y, int cols, int rows) {
    mvwaddch(window, y, x, ACS_ULCORNER);
    mvwaddch(window, y, x+cols-1, ACS_URCORNER);
    mvwaddch(window, y+rows-1, x, ACS_LLCORNER);
    mvwaddch(window, y+rows-1, x+cols-1, ACS_LRCORNER);
    for (int i = y+1; i < y+rows-1; i++) {
        mvwaddch(window, i, x, ACS_VLINE);
        mvwaddch(window, i, x+cols-1, ACS_VLINE);
    }
    for (int i = x+1; i < x+cols-1; i++) {
        mvwaddch(window, y, i, ACS_HLINE);
        mvwaddch(window, y+rows-1, i, ACS_HLINE);
    }
    wnoutrefresh(window);
}

// Bake text onto the window. Cannot change.
void Canvas::drawText(int x, int y, const char *text) {
    mvwaddstr(window, y, x, text);
    wnoutrefresh(window);
}

Canvas::~Canvas() {
    // Delete the Window and Panel
    del_panel(panel);
    delwin(window);
}

/* Second We Initialize the Elements */

/* Finally, the UI */

UI::UI()
{
    initializeCurses();
    initializeCanvases();
    //initializeElements();
}

void UI::initializeCanvases() {
    // Canvas(xPos, yPos, cols, rows, color, borderType)
    C_TITLE =       new Canvas(0, 0, 70, 5, getColorPair(Colors::WHITE), Borders::TOP);
    C_CONSOLE =     new Canvas(0, 4, 70, 3, getColorPair(Colors::WHITE), Borders::MIDDLE);
    C_LOBBY =       new Canvas(0, 6, 70, 26, getColorPair(Colors::WHITE), Borders::BOTTOM);
    C_SETTINGS =    new Canvas(35, 16, 34, 15, getColorPair(Colors::WHITE), Borders::FLOAT);
    C_CONTROLS =    new Canvas(0, 32, 70, 1, getColorPair(Colors::INVERT), Borders::NONE);
    C_MODE =        new Canvas(17, 7, 36, 21, getColorPair(Colors::WHITE), Borders::FLOAT);
    C_MATCH =       new Canvas(0, 6, 70, 26, getColorPair(Colors::WHITE), Borders::BOTTOM);

    /* Bake On Unchanging Elements */
    C_LOBBY->drawRow(9);
    C_SETTINGS->drawRow(2);
    C_SETTINGS->drawText(13, 1, "Settings");
    C_MATCH->drawRow(17);
    C_MATCH->drawRow(19);
    C_MATCH->drawText(1, 2, "Deck:");
    C_MATCH->drawBox(2, 5, 5, 11);

    hide_panel(C_TITLE->panel);
    hide_panel(C_CONSOLE->panel);
    hide_panel(C_LOBBY->panel);
    hide_panel(C_SETTINGS->panel);
    hide_panel(C_MODE->panel);
    hide_panel(C_MATCH->panel);

    update_panels();
    getch();

    show_panel(C_TITLE->panel);
    show_panel(C_CONSOLE->panel);
    show_panel(C_LOBBY->panel);
    show_panel(C_SETTINGS->panel);

    update_panels();

    doupdate();
}

/*
 * Initialize Curses with a standard configuration and start up color functionality.
 */
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

    box(stdscr, 0, 0);
    bkgd(getColorPair(Colors::GRAY));
    refresh();
}
/*
 * Initialize all UI elements (structs containing window, panel, and spatial information) for use in Uno.
 */
/*
void UI::initializeElements()
{
    // Create Elements with Default Values
    // Its pretty ugly...

    // Element(xPos, yPos, xDim, yDim, color, borderType, parent/tether)
    
    unsigned int WHITE = getColorPair(Colors::WHITE);

    el[Elements::TITLE] = new Element(0, 0, 70, 7, WHITE, Borders::TITLE, nullptr);

    el[Elements::WINDOW_MODE] = new Element(17, 7, 36, 21, WHITE, Borders::BOX, nullptr);
    el[Elements::MAIN_STAGE] = new Element(1, 1, 34, 4, WHITE, Borders::BOX, el[Elements::WINDOW_MODE]);
    el[Elements::BUTTON_LOCAL] = new Element(1, 8, 34, 3, WHITE, Borders::BOX, el[Elements::WINDOW_MODE]);
    el[Elements::BUTTON_HOST] = new Element(1, 11, 34, 3, WHITE, Borders::BOX, el[Elements::WINDOW_MODE]);
    el[Elements::BUTTON_JOIN] = new Element(1, 14, 34, 3, WHITE, Borders::BOX, el[Elements::WINDOW_MODE]);
    el[Elements::BUTTON_EXIT] = new Element(1, 17, 34, 3, WHITE, Borders::BOX, el[Elements::WINDOW_MODE]);

    el[Elements::WINDOW_LOBBY] = new Element(0, 6, 70, 26, WHITE, Borders::MIDDLE, nullptr);
    el[Elements::PLAYER_STAGE_0] = new Element(1, 1, 34, 4, WHITE, Borders::BOX, el[Elements::WINDOW_LOBBY]);
    el[Elements::PLAYER_STAGE_1] = new Element(35, 1, 34, 4, WHITE, Borders::BOX, el[Elements::WINDOW_LOBBY]);
    el[Elements::PLAYER_STAGE_2] = new Element(1, 5, 34, 4, WHITE, Borders::BOX, el[Elements::WINDOW_LOBBY]);
    el[Elements::PLAYER_STAGE_3] = new Element(35, 5, 34, 4, WHITE, Borders::BOX, el[Elements::WINDOW_LOBBY]);
    el[Elements::BUTTON_START] = new Element(1, 10, 34, 3, WHITE, Borders::BOX, el[Elements::WINDOW_LOBBY]);
    el[Elements::BUTTON_ADD_AI] = new Element(1, 13, 17, 3, WHITE, Borders::BOX, el[Elements::WINDOW_LOBBY]);
    el[Elements::BUTTON_SEARCH] = new Element(18, 13, 17, 3, WHITE, Borders::BOX, el[Elements::WINDOW_LOBBY]);
    el[Elements::BUTTON_KICK] = new Element(1, 16, 34, 3, WHITE, Borders::BOX, el[Elements::WINDOW_LOBBY]);
    el[Elements::BUTTON_CLOSE] = new Element(1, 19, 34, 3, WHITE, Borders::BOX, el[Elements::WINDOW_LOBBY]);
    el[Elements::BUTTON_SETTINGS] = new Element(1, 22, 34, 3, WHITE, Borders::BOX, el[Elements::WINDOW_LOBBY]);

    el[Elements::WINDOW_SETTINGS] = new Element(35, 16, 34, 15, WHITE, Borders::BOX, nullptr);
    el[Elements::BUTTON_DISPLAY_EFFECTS] = new Element(1, 3, 32, 1, WHITE, Borders::NONE, el[Elements::WINDOW_SETTINGS]);
    el[Elements::BUTTON_COMPUTER_SPEED] = new Element(1, 6, 32, 1, WHITE, Borders::NONE, el[Elements::WINDOW_SETTINGS]);
    el[Elements::BUTTON_SHOW_HANDS] = new Element(1, 9, 32, 1, WHITE, Borders::NONE, el[Elements::WINDOW_SETTINGS]);
    el[Elements::BUTTON_DOES_NOTHING] = new Element(1, 12, 32, 1, WHITE, Borders::NONE, el[Elements::WINDOW_SETTINGS]);

    el[Elements::WINDOW_MATCH] = new Element(0, 6, 70, 18, WHITE, Borders::MATCH, nullptr);
    el[Elements::WINDOW_HAND] = new Element(0, 23, 70, 9, WHITE, Borders::MIDDLE, nullptr);
    el[Elements::PREV_CARD] = new Element(2, 4, 4, 4, WHITE, Borders::BOX, el[Elements::WINDOW_HAND]);
    el[Elements::CARD_0] = new Element(7, 4, 4, 4, WHITE, Borders::BOX, el[Elements::WINDOW_HAND]);
    el[Elements::CARD_1] = new Element(11, 4, 4, 4, WHITE, Borders::BOX, el[Elements::WINDOW_HAND]);
    el[Elements::CARD_2] = new Element(15, 4, 4, 4, WHITE, Borders::BOX, el[Elements::WINDOW_HAND]);
    el[Elements::CARD_3] = new Element(19, 4, 4, 4, WHITE, Borders::BOX, el[Elements::WINDOW_HAND]);
    el[Elements::CARD_4] = new Element(23, 4, 4, 4, WHITE, Borders::BOX, el[Elements::WINDOW_HAND]);
    el[Elements::CARD_5] = new Element(27, 4, 4, 4, WHITE, Borders::BOX, el[Elements::WINDOW_HAND]);
    el[Elements::CARD_6] = new Element(31, 4, 4, 4, WHITE, Borders::BOX, el[Elements::WINDOW_HAND]);
    el[Elements::CARD_7] = new Element(35, 4, 4, 4, WHITE, Borders::BOX, el[Elements::WINDOW_HAND]);
    el[Elements::CARD_8] = new Element(39, 4, 4, 4, WHITE, Borders::BOX, el[Elements::WINDOW_HAND]);
    el[Elements::CARD_9] = new Element(43, 4, 4, 4, WHITE, Borders::BOX, el[Elements::WINDOW_HAND]);
    el[Elements::CARD_10] = new Element(47, 4, 4, 4, WHITE, Borders::BOX, el[Elements::WINDOW_HAND]);
    el[Elements::CARD_11] = new Element(51, 4, 4, 4, WHITE, Borders::BOX, el[Elements::WINDOW_HAND]);
    el[Elements::CARD_12] = new Element(55, 4, 4, 4, WHITE, Borders::BOX, el[Elements::WINDOW_HAND]);
    el[Elements::CARD_13] = new Element(59, 4, 4, 4, WHITE, Borders::BOX, el[Elements::WINDOW_HAND]);
    el[Elements::NEXT_CARD] = new Element(64, 4, 4, 4, WHITE, Borders::BOX, el[Elements::WINDOW_HAND]);

    el[Elements::DECK_METER] = new Element(2, 5, 5, 11, WHITE, Borders::BOX, el[Elements::WINDOW_MATCH]);
    el[Elements::DECK_COUNT] = new Element(1, 2, 9, 2, WHITE, Borders::NONE, el[Elements::WINDOW_MATCH]);
    el[Elements::BELOW_CARD] = new Element(27, 2, 14, 12, WHITE, Borders::BOX, el[Elements::WINDOW_MATCH]);
    el[Elements::TOP_CARD] = new Element(29, 4, 14, 12, WHITE, Borders::BOX, el[Elements::WINDOW_MATCH]);
    el[Elements::PLAYER_TILE_0] = new Element(55, 1, 14, 4, WHITE, Borders::BOX, el[Elements::WINDOW_MATCH]);
    el[Elements::PLAYER_TILE_1] = new Element(55, 5, 14, 4, WHITE, Borders::BOX, el[Elements::WINDOW_MATCH]);
    el[Elements::PLAYER_TILE_2] = new Element(55, 9, 14, 4, WHITE, Borders::BOX, el[Elements::WINDOW_MATCH]);
    el[Elements::PLAYER_TILE_3] = new Element(55, 13, 14, 4, WHITE, Borders::BOX, el[Elements::WINDOW_MATCH]);

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
    ElementUpdate data[14] = {
            ElementUpdate(Elements::BUTTON_START, 11, 32, "Start Game", false, Colors::DEFAULT, false),
            ElementUpdate(Elements::BUTTON_ADD_AI, 5, 15, "Add AI", false, Colors::DEFAULT, false),
            ElementUpdate(Elements::BUTTON_SEARCH, 4, 15, "Search", false, Colors::DEFAULT, false),
            ElementUpdate(Elements::BUTTON_KICK, 11, 32, "Kick Player", false, Colors::DEFAULT, false),
            ElementUpdate(Elements::BUTTON_CLOSE, 11, 32, "Close Room", false, Colors::DEFAULT, false),
            ElementUpdate(Elements::BUTTON_SETTINGS, 12, 32, "Settings", false, Colors::DEFAULT, false),
            ElementUpdate(Elements::BUTTON_HOST, 8, 32, "Host Multiplayer", false, Colors::DEFAULT, false),
            ElementUpdate(Elements::BUTTON_JOIN, 8, 32, "Join Multiplayer", false, Colors::DEFAULT, false),
            ElementUpdate(Elements::BUTTON_LOCAL, 7, 32, "Local Singleplayer", false, Colors::DEFAULT, false),
            ElementUpdate(Elements::BUTTON_EXIT, 14, 32, "Exit", false, Colors::DEFAULT, false),
            ElementUpdate(Elements::BUTTON_DISPLAY_EFFECTS, 0, 32, "- Display Effects", false, Colors::DEFAULT, true),
            ElementUpdate(Elements::BUTTON_COMPUTER_SPEED, 0, 32, "- Computer Speed", false, Colors::DEFAULT, true),
            ElementUpdate(Elements::BUTTON_SHOW_HANDS, 0, 32, "- Show Computer Hands", false, Colors::DEFAULT, true),
            ElementUpdate(Elements::BUTTON_DOES_NOTHING, 0, 32, "- Does Nothing", false, Colors::DEFAULT, true),
    };
    updateButtons(data, updateSize);


    // Finally, Hide Everything Except stdscr
    for (auto it=el.begin(); it!=el.end(); it++)
        if (it->first != Elements::MAIN)
            hide_panel(it->second->panel);
    updatePanels();

    show_panel(el[Elements::TITLE]->panel);
    updatePanels();

}
*/



/*
 *  Delete all canvases and elements stored in the UI
 *  one by one...
 */
UI::~UI()
{

    /* Delete Canvases */
    //delete C_TITLE;
    //delete C_CONSOLE;
    //delete C_MODE;
    //delete C_LOBBY;
    //delete C_MATCH;
    //delete C_SETTINGS;

    endwin();
}