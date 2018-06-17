//
// Created by Brandon Martin on 6/13/18.
//

#ifndef UNO_ONLINE_MULTIPLAYER_UI_H
#define UNO_ONLINE_MULTIPLAYER_UI_H

#include "ui_elements.h"
#include <map>


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

    void colorElement(Elements, Colors);
    void initializeCanvases();
    void initializeCurses();
    void initializeElements();
    void printToConsole(const char*, Colors);
    void printToModeConsole(const char*, Colors);
    void putChar(Elements, int, int, char, Colors = Colors::DEFAULT);
    void putText(Elements, int, int, const char*, Colors = Colors::DEFAULT);
    void putSpecialChar(Elements element, int x, int y, chtype character, Colors color);

    static void updatePanels();

    /* Canvases */
    Canvas* C_TITLE;
    Canvas* C_CONSOLE;
    Canvas* C_MODE;
    Canvas* C_LOBBY;
    Canvas* C_MATCH;
    Canvas* C_SETTINGS;
    Canvas* C_CONTROLS;

    /* Elements */



};


#endif //UNO_ONLINE_MULTIPLAYER_UI_H
