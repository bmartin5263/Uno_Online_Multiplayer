//
// Created by Brandon Martin on 6/15/18.
//

/*
 * This file contains all the initializing information for the UI
 */

#include "ui.h"
#include "cstring"
#include "assert.h"

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

AbstractElement::AbstractElement(const Canvas *defaultCanvas, int x, int y, int length, int height) :
    canvas(defaultCanvas), x(x), y(y), length(length), height(height)
{
}

AbstractElement::~AbstractElement() {
    // Nothing
}

void AbstractElement::move(int newX, int newY) {
    this->x = newX;
    this->y = newY;
}

void AbstractElement::setCanvas(const Canvas * defaultCanvas) {
    this->canvas = defaultCanvas;
}

Element_1D::Element_1D(const Canvas *defaultCanvas, int x, int y, int length, int defaultAttribute) :
    AbstractElement(defaultCanvas, x, y, length, 1), defaultAttribute(defaultAttribute), attr(-1)
{
    body = new char[length+1];
}

// Clear the body and render the result
void Element_1D::clearElement() {
    memset(body, ' ', (size_t)length);
    body[length] = '\0';
    this->render();
}

// Draw element onto the default canvas
void Element_1D::render() {
    this->renderOnto(*canvas);
}

void Element_1D::renderV() {
    this->renderOntoV(*canvas);
}

void Element_1D::renderOnto(const Canvas& canvas) {
    assert(body != nullptr);
    WINDOW* window = canvas.window;
    if (attr >= 0)
        wattron(window, attr);
    else
        wattron(window, defaultAttribute);
    mvwprintw(window, y, x, body);
    if (attr >= 0)
        wattroff(window, attr);
    else
        wattroff(window, defaultAttribute);
    wnoutrefresh(canvas.window);
}

void Element_1D::renderOntoV(const Canvas& canvas) {
    assert(body != nullptr);
    WINDOW* window = canvas.window;
    if (attr >= 0)
        wattron(window, attr);
    else
        wattron(window, defaultAttribute);
    for (int i = 0; i < length; i++) {
        mvwaddch(window, y+i, x, (chtype)body[i]);
    }
    if (attr >= 0)
        wattroff(window, attr);
    else
        wattroff(window, defaultAttribute);
    wnoutrefresh(canvas.window);
}

void Element_1D::setAttribute(int attr) {
    this->attr = attr;
}

void Element_1D::setBody(const char *newBody) {
    if (newBody != nullptr) {
        this->clearElement();
        strncpy(body, newBody, (size_t)length);
    }
}

Element_1D::~Element_1D() {
    beep();
    delete body;
}

Label::Label(const Canvas *defaultCanvas, int x, int y, int length, int defaultAttribute) :
    Element_1D(defaultCanvas, x, y, length, defaultAttribute)
{
}

void Label::setText(const char *text, int attr) {
    this->setAttribute(attr);
    this->setBody(text);
    this->render();
}

CardCount::CardCount(Canvas *defaultCanvas, int x, int y) :
    Label(defaultCanvas, x, y, DECK_COUNT_LABEL_LEN, 0)
{
}

void CardCount::setValue(const int val) {
    char str[DECK_COUNT_LABEL_LEN+1];
    snprintf(str, (size_t)length+1, "%i Cards", val);
    setText(str);
}

HandName::HandName(Canvas *defaultCanvas, int x, int y) :
    Label(defaultCanvas, x, y, HAND_NAME_LABEL_LEN, 0)
{
}

void HandName::setName(const char* name) {
    char str[HAND_NAME_LABEL_LEN+1];
    snprintf(str, (size_t)length+1, "%s's Hand", name);
    setText(str);
}

HandMeter::HandMeter(Canvas *defaultCanvas, int x, int y) :
    Label(defaultCanvas, x, y, HAND_METER_LEN, 0)
{
}

void HandMeter::setSizeAndPos(const int size, const int pos) {
    assert(pos <= size);
    char str[HAND_NAME_LABEL_LEN+1];
    str[0] = '[';
    for (int i = 1; i < HAND_METER_LEN; i++) {
        if (i <= size) {
            if (pos == i) str[i] = '|';
            else str[i] = '-';
        }
        else str[i] = ' ';
    }
    str[size+1] = ']';
    str[HAND_METER_LEN] = '\0';
    setText(str);
}

//////////////////////////////////////////////////////////////////////////////////
/*
Element::Element() :
        defaultCanvas(nullptr), x(0), y(0), body(nullptr), cols(0), rows(0), attribute(0)
{
    // Nothing
}

Element::Element(const Canvas* canvas, int locX, int locY, int attribute) :
        defaultCanvas(canvas), x(locX), y(locY), body(nullptr), cols(0), rows(0), attribute(attribute)
{
}

Element::Element(const Canvas *defaultCanvas, int locX, int locY, char **body, int cols, int rows, int attribute) :
        defaultCanvas(defaultCanvas), x(locX), y(locY), body(body), cols(cols), rows(rows), attribute(attribute)
{
    // Nothing to see here
}

void Element::setAttribute(int attr) {
    this->attribute = attr;
}

void Element::setBody(char **newBody, int cols, int rows) {
    if (body != nullptr) {
        // Clear the old text
        this->clearElement();
        this->render();
        // Delete the old text
        this->deleteBody();
    }
    // Set up the new text
    this->rows = rows;
    this->cols = cols;
    this->body = newBody;
}

// Print whitespace over the body of the element, clearing it from the canvas
void Element::clearElement() {
    for (int i = 0; i < rows; i++) {
        memset(body[i], ' ', (size_t)cols);
        body[i][cols] = '\0';
    }
}

// Draw element onto the default canvas
void Element::render() {
    assert(defaultCanvas != nullptr);
    this->renderOnto(*defaultCanvas);
}


void Element::renderOnto(const Canvas& canvas) {
    assert(body != nullptr);
    WINDOW* window = canvas.window;
    if (attribute >= 0)
        wattron(window, attribute);
    for (int i = 0; i < rows; i++) {
        mvwprintw(canvas.window, y+i, x, body[i]);
    }
    if (attribute >= 0)
        wattroff(window, attribute);
    wnoutrefresh(canvas.window);
}

void Element::setCanvas(const Canvas * canvas) {
    this->defaultCanvas = canvas;
}

void Element::deleteBody() {
    for(int i = 0; i < rows; i++)
        delete[] body[i];
    delete[] body;
    body = nullptr;
}

Element::~Element() {
    // Delete Skeleton Text
    deleteBody();
}

Label::Label(const Canvas* defaultCanvas, int locX, int locY, const int totalLength) :
        Element(defaultCanvas, locX, locY, -1), totalLength(totalLength)
{
}

Label::Label(const Canvas *defaultCanvas, int locX, int locY, int totalLength, int attr) :
        Element(defaultCanvas, locX, locY, attr), totalLength(totalLength)
{
}

void Label::setText(const char *text, int attr) {
    // Dynamically Allocate the string array
    auto **strArr = new char*[1];
    strArr[0] = new char[totalLength+1];
    strncpy(strArr[0],text, (size_t)totalLength);
    // Pass the responsibility to deallocate to the element
    if (attr >= 0)
        this->setAttribute(attr);
    this->setBody(strArr, totalLength, 1);
}

HandMeter::HandMeter(const Canvas *defaultCanvas, int locX, int locY) :
    Label(defaultCanvas, locX, locY, HAND_METER_LEN)
{
}

// [] = 0,0
void HandMeter::setSizeAndPos(int size, int pos) {
    char str[HAND_METER_LEN];
    str[0] = '[';
    for (int i = 1; i < HAND_METER_LEN; i++) {
        if (i <= size) {
            if (pos == i) str[i] = '|';
            else str[i] = '-';
        }
        else str[i] = ' ';
    }
    str[size+1] = ']';
    setText(str, -1);
}

DeckMeter::DeckMeter(const Canvas *defaultCanvas, int locX, int locY, int deckSize) :
    Label(defaultCanvas, locX, locY, 1), deckSize(deckSize)
{
}
*/

UI::UI()
{
    initializeCurses();
    initializeCanvases();
    initializeElements();
}

void UI::initializeCanvases() {
    const unsigned int white = COLOR_PAIR(1);

    // Canvas(xPos, yPos, cols, rows, color, borderType)
    C_TITLE =       new Canvas(0, 0, 70, 5, white, Borders::TOP);
    C_CONSOLE =     new Canvas(0, 4, 70, 3, white, Borders::MIDDLE);
    C_LOBBY =       new Canvas(0, 6, 70, 26, white, Borders::BOTTOM);
    C_SETTINGS =    new Canvas(35, 16, 34, 15, white, Borders::FLOAT);
    C_CONTROLS =    new Canvas(0, 32, 70, 1, white, Borders::NONE);
    C_MODE =        new Canvas(17, 7, 36, 21, white, Borders::FLOAT);
    C_MATCH =       new Canvas(0, 6, 70, 26, white, Borders::BOTTOM);
    C_BELOW_CARD =  new Canvas(27, 8, 14,12, white, Borders::FLOAT);
    C_TOP_CARD =    new Canvas(29, 11, 14,12, white, Borders::FLOAT);

    /* Bake On Unchanging Elements */
    //C_LOBBY->drawRow(9);
    //C_SETTINGS->drawRow(2);
    //C_SETTINGS->drawText(13, 1, "Settings");
    C_MATCH->drawRow(17);
    C_MATCH->drawRow(19);
    C_MATCH->drawText(1, 2, "Deck:");
    C_MATCH->drawBox(2, 5, 5, 11);
    //C_MODE->drawRow(5);
    //C_MODE->drawRow(7);

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

void UI::initializeElements()
{
    // Create Elements with Default Values
    /*
    auto **b = new char*[2];
    b[0] = new char[sizeof("My Default")];
    b[1] = new char[sizeof("Element")];
    strcpy(b[0],"My Default");
    strcpy(b[1],"Element");
    */
    /*
    E_CONSOLE = new Label(C_CONSOLE, 1, 1, CONSOLE_LABEL_LEN, getColorPair(Colors::YELLOW));
    E_CONSOLE->setText("Console Initialized");
    E_CONSOLE->render();

    E_MODE_CONSOLE = new Label(C_MODE, 1, 6, MODE_CONSOLE_LABEL_LEN, getColorPair(Colors::YELLOW));
    E_MODE_CONSOLE->setText("Mode Console Initialized");
    E_MODE_CONSOLE->render();

    E_DECK_COUNT = new Label(C_MATCH, 1, 3, DECK_COUNT_LABEL_LEN);
    E_DECK_COUNT->setText("999 Cards");
    E_DECK_COUNT->render();

    E_HAND_NAME = new Label(C_MATCH, 1, 18, HAND_NAME_LABEL_LEN);
    E_HAND_NAME->setText("aaaaaaaaaaaa's Hand");
    E_HAND_NAME->render();

    E_HAND_METER = new HandMeter(C_MATCH, 55, 18);
    E_HAND_METER->setSizeAndPos(0,0);
    E_HAND_METER->render();
    */

    E_CONSOLE = new Label(C_CONSOLE, 1, 1, CONSOLE_LABEL_LEN, getColorPair(Colors::YELLOW));
    E_CONSOLE->setText("Console Initialized", getColorPair(Colors::GRAY));

    E_MODE_CONSOLE = new Label(C_MODE, 1, 6, MODE_CONSOLE_LABEL_LEN, getColorPair(Colors::YELLOW));
    E_MODE_CONSOLE->setText("Mode Console Initialized", getColorPair(Colors::GRAY));

    E_HAND_NAME = new HandName(C_MATCH, 1, 18);
    E_HAND_NAME->setName("Anonymous");

    E_HAND_METER = new HandMeter(C_MATCH, 55, 18);
    E_HAND_METER->setSizeAndPos(5,1);

    E_CARD_COUNT = new CardCount(C_MATCH, 1, 3);
    E_CARD_COUNT->setValue(999);

    doupdate();

}



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