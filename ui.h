//
// Created by Brandon Martin on 6/13/18.
//

#ifndef UNO_ONLINE_MULTIPLAYER_UI_H
#define UNO_ONLINE_MULTIPLAYER_UI_H

#include <ncurses.h>
#include <panel.h>
#include <map>

#define START_LABEL = "Start Game"

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

enum class Colors {
    BLUE, RED, GREEN, YELLOW, WHITE, GRAY, INVERT, WILD, DEFAULT
};

enum class Borders { BOX, TITLE, MIDDLE, MATCH, NONE };

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

class UI {

public:

    // Big Four
    UI();
    UI(const UI &other) = delete;
    UI& operator = (const UI &t) = delete;
    ~UI();

    void updateButtons(ButtonUpdate*, int length);
    void Run();

    std::map<Colors, unsigned int> TEXT_COLORS;      // Pretty Much Static, But Has to be Initialized at Runtime
    std::map<Elements, Element*> el;                 // el = Elements

private:

    void colorElement(Elements, Colors);
    void initializeCurses();
    void initializeElements();
    void putChar(Elements, int, int, char, Colors = Colors::DEFAULT);
    void putText(Elements, int, int, const char*, Colors = Colors::DEFAULT);
    void putSpecialChar(Elements element, int x, int y, chtype character, Colors color);
    static void updatePanels();

};


#endif //UNO_ONLINE_MULTIPLAYER_UI_H
