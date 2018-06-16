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


ButtonUpdate::ButtonUpdate(Elements element, int start, int length, const char *label, bool active, Colors color, bool startAtZero)
: element(element), start(start), length(length), label(label), active(active), color(color), startAtZero(startAtZero) {
    // Nothing to do
}

Element::Element(const int locX, const int locY, const int dimX, const int dimY,
                 const unsigned int color, const Borders border, Element* const tether)
: x(locX), y(locY), size_x(dimX), size_y(dimY), defaultColor(color), tetheredElement(tether)
{
    if (tetheredElement != nullptr) {
        // Adjust relative location to absolute
        x += tetheredElement->x;
        y += tetheredElement->y;
    }

    window = newwin(size_y, size_x, y, x);
    panel = new_panel(window);

    switch (border) {
        case Borders::BOX :
            box(window, 0, 0);
            break;
        case Borders::TITLE:
            wborder(window, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LTEE, ACS_RTEE);
            break;
        case Borders::MIDDLE:
            wborder(window, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_LTEE, ACS_RTEE, ACS_LLCORNER, ACS_LRCORNER);
            break;
        case Borders::MATCH:
            wborder(window, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_LTEE, ACS_RTEE, ACS_LTEE, ACS_RTEE);
            break;
        case Borders::NONE:
            break;
    }

    wbkgd(window, color);
    wnoutrefresh(window);

}

Element::~Element()
{
    del_panel(panel);
    delwin(window);
}

void UI::colorElement(const Elements element, const Colors color) {
    WINDOW* window = el[element]->window;
    unsigned int colorVal;
    if (color == Colors::DEFAULT) colorVal = el[element]->defaultColor;
    else colorVal = TEXT_COLORS[color];

    // Color the Window
    wbkgd(window, colorVal);
    wattrset(window, colorVal);
    wnoutrefresh(window);

}

void UI::putChar(Elements element, int x, int y, const char character, Colors color) {
    WINDOW* window = this->el[element]->window;
    unsigned int colorVal;
    if (color != Colors::DEFAULT)
        colorVal = this->TEXT_COLORS[color];
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
        colorVal = this->TEXT_COLORS[color];
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
        colorVal = this->TEXT_COLORS[color];
    else
        colorVal = this->el[element]->defaultColor;
    wattron(window, colorVal);
    mvwaddstr(window, y, x, text);
    wattroff(window, colorVal);
    wnoutrefresh(window);
}

void UI::updateButtons(ButtonUpdate *data, int length){
    for (int i = 0; i < length; i++) {
        // Get the struct
        ButtonUpdate bu = data[i];
        // Fix the color
        Colors color = bu.color;
        if (!bu.active)
            color = Colors::GRAY;
        colorElement(bu.element, color);
        // Put the label, clearing the old one
        std::string str = std::string((unsigned long)bu.length, ' ');
        if (bu.startAtZero) {
            putText(bu.element, 0, 0, str.c_str(), color);
            putText(bu.element, bu.start + 1, 0, bu.label, color);
        } else {
            putText(bu.element, 1, 1, str.c_str(), color);
            putText(bu.element, bu.start + 1, 1, bu.label, color);
        }
    }
    doupdate();

}

void UI::Run()
{
    getch();
    //beep();
}