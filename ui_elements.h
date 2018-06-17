//
// Created by Brandon Martin on 6/16/18.
//

#ifndef UNO_ONLINE_MULTIPLAYER_UI_ELEMENTS_H
#define UNO_ONLINE_MULTIPLAYER_UI_ELEMENTS_H

#include <ncurses.h>
#include <panel.h>

enum class Elements {
    MAIN, TITLE, WINDOW_MODE, MAIN_STAGE, BUTTON_LOCAL, BUTTON_HOST, BUTTON_JOIN,
    BUTTON_EXIT, WINDOW_LOBBY, PLAYER_STAGE_0, PLAYER_STAGE_1, PLAYER_STAGE_2,
    PLAYER_STAGE_3, BUTTON_START, BUTTON_ADD_AI, BUTTON_SEARCH, BUTTON_KICK,
    BUTTON_CLOSE, BUTTON_SETTINGS, WINDOW_SETTINGS, BUTTON_DISPLAY_EFFECTS,
    BUTTON_COMPUTER_SPEED, BUTTON_SHOW_HANDS, BUTTON_DOES_NOTHING,
    WINDOW_HAND, WINDOW_MATCH, TOP_CARD, BELOW_CARD, DECK_METER, DECK_COUNT,
    CARD_0, CARD_1, CARD_2, CARD_3, CARD_4, CARD_5, CARD_6, CARD_7, CARD_8,
    CARD_9, CARD_10, CARD_11, CARD_12, CARD_13, PLAYER_TILE_0, PLAYER_TILE_1,
    PLAYER_TILE_2, PLAYER_TILE_3, NEXT_CARD, PREV_CARD
};

enum class Canvases {
    TITLE, LOBBY, MATCH, MODE, CONSOLE, SETTINGS, CONTROLS
};

enum class Colors {
    BLUE, RED, GREEN, YELLOW, WHITE, GRAY, INVERT, WILD, DEFAULT
};

enum class Borders {
    TOP, MIDDLE, BOTTOM, FLOAT, NONE
};

/*
 * Class: Canvas
 *
 * Canvases are Window/Panel pairs that carry with them metadata about their size, initial color,
 * and location on the screen. They serve as a drawing board where elements can render their contents
 * onto and can be easily hidden when not in use.
 */
class Canvas {

public:
    Canvas(int locX, int locY, int dimX, int dimY, unsigned int color, Borders borders);
    ~Canvas();

    // No Copying Right Now...
    Canvas(const Canvas &other) = delete;
    Canvas& operator = (const Canvas & other) = delete;

    void drawRow(int y);
    void drawText(int x, int y, const char* text);
    void drawBox(int x, int y, int cols, int rows);

    WINDOW* window;
    PANEL* panel;

private:
    int x;
    int y;
    int cols;
    int rows;
    unsigned int defaultColor;
};

/*
 * Class: Element
 *
 * Elements are various TUI components that are rendered (drawn) onto Canvases. Element is the base
 * class for all specialized elements (such as Label, Card, Button, etc) that provides the methods update
 * and render. Elements should not store information within them other than the string to print onto the canvas
 * and should only have updates done to that state.
 *
 * Element in its base class acts as an unchangeable string that represents the Element's skeleton.
 */
/*
class Element {
public:
    Element(const char* skeleton, int locX, int locY, int dimX, int dimY, unsigned int color, Canvas* defaultCanvas);
    ~Elemental();

    // No Copying Right Now...
    Element(const Element &other) = delete;
    Element& operator = (const Element & other) = delete;

    virtual void update() = 0;
    virtual void render();  // Render onto default canvas
    virtual void renderOnto(const Canvas*);  // Render onto specified canvas

private:

    const char* skeleton;
    Canvas* defaultCanvas;
    unsigned int color;

};

class Label : public Element {
public:
    Label(const char* text, Canvas* defaultCanvas);
    ~Label();
};
*/
#endif //UNO_ONLINE_MULTIPLAYER_UI_ELEMENTS_H
