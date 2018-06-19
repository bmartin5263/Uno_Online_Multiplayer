//
// Created by Brandon Martin on 6/13/18.
//

#ifndef UNO_ONLINE_MULTIPLAYER_UI_H
#define UNO_ONLINE_MULTIPLAYER_UI_H

#include "ui_elements.h"
#include <map>

#define CONSOLE_LABEL_LEN 68
#define MODE_CONSOLE_LABEL_LEN 34
#define DECK_COUNT_LABEL_LEN 9
#define HAND_NAME_LABEL_LEN 19
#define HAND_METER_LEN 14

/*
 * Class: UI
 *
 * The UI class provides an API for updating and drawing various elements and canvases and manipulate
 * them through predefined public methods specific to the game Uno and helper private methods for performing
 * various curses tasks.
 */
class UI {

public:

    // Big Four
    UI();
    UI(const UI &other) = delete;
    UI& operator = (const UI &t) = delete;
    ~UI();

    static unsigned int getColorPair(Colors);

    void console(const char*);
    void consoleMode(const char*);
    void run();
    void warning(const char*);
    void warningMode(const char*);

    //std::map<Elements, Element*> el;                 // el = Elements

private:

    void initializeCanvases();
    void initializeCurses();
    void initializeElements();
    void printToConsole(const char*, Colors);
    void printToModeConsole(const char*, Colors);

    static void updatePanels();

    /* Canvases */
    Canvas* C_TITLE;
    Canvas* C_CONSOLE;
    Canvas* C_MODE;
    Canvas* C_LOBBY;
    Canvas* C_MATCH;
    Canvas* C_SETTINGS;
    Canvas* C_CONTROLS;
    Canvas* C_TOP_CARD;
    Canvas* C_BELOW_CARD;

    /* Elements */
    //Label* E_CONSOLE;
    //Label* E_MODE_CONSOLE;
    //Label* E_DECK_COUNT;
    //Label* E_HAND_NAME;
    //HandMeter* E_HAND_METER;
    //DeckMete* E_DECK_METER;

    Label* E_CONSOLE;
    Label* E_MODE_CONSOLE;
    HandName* E_HAND_NAME;
    HandMeter* E_HAND_METER;
    CardCount* E_CARD_COUNT;


};

#endif //UNO_ONLINE_MULTIPLAYER_UI_H
