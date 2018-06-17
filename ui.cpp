//
// Created by Brandon Martin on 6/13/18.
//
#include "ui.h"
#include <string>
//#include <curses.h>

void UI::updatePanels() {
    update_panels();
    doupdate();
}

// Return a curses color pair for a specified color
unsigned int UI::getColorPair(Colors color) {
    switch (color) {
        case Colors::WILD:
        case Colors::DEFAULT:
        case Colors::WHITE:
            return COLOR_PAIR(1);
        case Colors::BLUE:
            return COLOR_PAIR(2);
        case Colors::RED:
            return COLOR_PAIR(3);
        case Colors::GREEN:
            return COLOR_PAIR(4);
        case Colors::YELLOW:
            return COLOR_PAIR(5);
        case Colors::INVERT:
            return COLOR_PAIR(6);
        case Colors::GRAY:
            return COLOR_PAIR(11);
    }
}
/*
void UI::putChar(Elements element, int x, int y, const char character, Colors color) {
    WINDOW* window = this->el[element]->window;
    unsigned int colorVal;
    if (color != Colors::DEFAULT)
        colorVal = this->getColorPair(color);
    else
        colorVal = this->el[element]->defaultColor;
    wattr_on(window, colorVal, nullptr);
    mvwaddch(window, y, x, (const chtype)character);
    wattr_off(window, colorVal, nullptr);
    wnoutrefresh(window);
}

void UI::putSpecialChar(Elements element, int x, int y, const chtype character, Colors color) {
    // Used specifically for curses macros
    WINDOW* window = this->el[element]->window;
    unsigned int colorVal;
    if (color != Colors::DEFAULT)
        colorVal = this->getColorPair(color);
    else
        colorVal = this->el[element]->defaultColor;
    wattron(window, colorVal);
    mvwaddch(window, y, x, character);
    wattroff(window, colorVal);
    wnoutrefresh(window);
}

void UI::putText(const Elements element, const int x, const int y, const char* text, const Colors color) {
    WINDOW* window = this->el[element]->window;
    unsigned int colorVal;
    if (color != Colors::DEFAULT)
        colorVal = this->getColorPair(color);
    else
        colorVal = this->el[element]->defaultColor;
    wattron(window, colorVal);
    mvwaddstr(window, y, x, text);
    wattroff(window, colorVal);
    wnoutrefresh(window);
}

*/
void UI::run()
{
    getch();
    //beep();
}