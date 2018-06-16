//
// Created by Brandon Martin on 6/13/18.
//

#ifndef UNO_ONLINE_MULTIPLAYER_UI_H
#define UNO_ONLINE_MULTIPLAYER_UI_H

#include <ncurses.h>
#include <panel.h>
#include <map>

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
    TITLE, LOBBY, MATCH, MODE, CONSOLE
};

enum class Colors {
    BLUE, RED, GREEN, YELLOW, WHITE, GRAY, INVERT, WILD, DEFAULT
};

enum class Borders {
    BOX, TITLE, MIDDLE, MATCH, NONE
};

enum class Groups {
    MODE, LOBBY, SETTINGS, DEFAULT, STAGE, MATCH
};

struct ButtonUpdate {

    ButtonUpdate(Elements element, int start, int length, const char * label, bool active, Colors color, bool startAtZero);
    ~ButtonUpdate() = default;

    const char* label;
    int start;
    int length;
    Colors color;
    Elements element;
    bool active;
    bool startAtZero;

};

struct Element {
    // Big Four
    Element(int locX, int locY, int dimX, int dimY, unsigned int color, Borders border, Element* tether);
    // No Copying
    Element(const Element &other) = delete;
    Element& operator = (const Element & other) = delete;
    ~Element();

    WINDOW* window;
    PANEL* panel;
    Element* tetheredElement;

    int x;
    int y;
    int size_x;
    int size_y;
    unsigned int defaultColor;

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
    Canvas(int locX, int locY, int dimX, int dimY, unsigned int color, Borders border);
    ~Canvas();

    // No Copying Right Now...
    Canvas(const Canvas &other) = delete;
    Canvas& operator = (const Canvas & other) = delete;

    WINDOW* window;
    PANEL* panel;

private:
    int x;
    int y;
    int columnss;
    int lines;
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
class Elemental {
public:
    Elemental(const char* skeleton, int locX, int locY, int dimX, int dimY, Canvas* defaultCanvas);
    ~Elemental();

    // No Copying Right Now...
    Elemental(const Elemental &other) = delete;
    Elemental& operator = (const Elemental & other) = delete;

    virtual void update() = 0;
    virtual void render();  // Render onto default canvas
    virtual void renderOnto(const Canvas*);  // Render onto specified canvas

private:

    const char* skeleton;
    Canvas* defaultCanvas;
    unsigned int color;

};

class Label : public Elemental {
public:
    Label(const char* text, const char* skeleton, Canvas* defaultCanvas);
    ~Label();
};


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
    void updateButtons(ButtonUpdate*, int length);
    void warning(const char*);
    void warningMode(const char*);

    std::map<Elements, Element*> el;                 // el = Elements

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

};


#endif //UNO_ONLINE_MULTIPLAYER_UI_H
