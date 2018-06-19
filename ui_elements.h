//
// Created by Brandon Martin on 6/16/18.
//

#ifndef UNO_ONLINE_MULTIPLAYER_UI_ELEMENTS_H
#define UNO_ONLINE_MULTIPLAYER_UI_ELEMENTS_H

#include <ncurses.h>
#include <panel.h>

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
 * Class: AbstractElement
 *
 * Elements are various TUI components that are rendered (drawn) onto Canvases. AbstractElement is the base
 * class for all elements, one-dimensional or two (such as Label, Card, Button, etc) that defines the required
 * methods to render onto Canvases. Elements will typically have a body that defines the string to draw, but it
 * first must be subclassed to define what that body actually is.
 */

class AbstractElement {
public:
    AbstractElement(const Canvas* defaultCanvas, int x, int y, int length, int height);
    // No Copying Right Now...
    AbstractElement(const AbstractElement &other) = delete;
    AbstractElement& operator = (const AbstractElement & other) = delete;
    virtual ~AbstractElement() = 0;

    void move(int newX, int newY);
    virtual void render() = 0;                          // Standard Horizontal Render onto canvas property
    virtual void renderOnto(const Canvas&) = 0;         // Standard Horizontal Render onto specified canvas
    virtual void renderV() = 0;                         // Vertically Render onto canvas property
    virtual void renderOntoV(const Canvas&) = 0;        // Vertically Render onto specified canvas
    void setCanvas(const Canvas*);

    const Canvas* canvas;
    int x;                          // X value of top-left corner
    int y;                          // Y value of top-left corner
    int length;                     // doubles as height for vertical rendering
    int height;                     // doubles as length for vertical rendering
};

/*
 * Class: Element_1D
 *
 * Element_1D is the base class for all elements that consist of only one horizontal or vertical dimension.
 * The body of 1-D elements consist of a single string and has an additional member variable for attributes.
 * This and Element_2D serve as the first layer for more complex elements that have multiple attributes and text
 * bodies pasted on top of each other.
 */

class Element_1D : public AbstractElement {
public:
    Element_1D(const Canvas* defaultCanvas, int x, int y, int length, int defaultAttribute);
    Element_1D(const Element_1D &other) = delete;
    Element_1D& operator = (const Element_1D & other) = delete;
    virtual ~Element_1D();

    virtual void clearElement();
    virtual void render();
    virtual void renderOnto(const Canvas&);
    virtual void renderV();
    virtual void renderOntoV(const Canvas&);
    virtual void setAttribute(int attr);                        // Pass -1 to use default attribute
    virtual void setBody(const char* body);


private:
    char* body;
    const int defaultAttribute;               // Use -1 for no attribute
    int attr;

};

/*
 * Class: Label
 *
 * Labels are Element_1D's that only support horizontal rendering of text. Labels give a concise interface
 * for rendering text with various attributes onscreen.
 *
 * Derivatives of Label provide unique methods for accepting data that is used to create the full string
 * body.
 */

class Label : public Element_1D {
public:
    Label(const Canvas* defaultCanvas, int x, int y, int length, int defaultAttribute);
    Label(const Label &other) = delete;
    Label& operator = (const Label & other) = delete;

    void setText(const char* text, int attr=-1);
};

class CardCount : public Label {
public:
    CardCount(Canvas* defaultCanvas, int x, int y);
    CardCount(const CardCount &other) = delete;
    CardCount& operator = (const CardCount & other) = delete;

    void setValue(const int val);
};

class HandName : public Label {
public:
    HandName(Canvas* defaultCanvas, int x, int y);
    HandName(const HandName &other) = delete;
    HandName& operator = (const HandName & other) = delete;

    void setName(const char* name);
};

class HandMeter : public Label {
public:

    HandMeter(Canvas* defaultCanvas, int x, int y);
    HandMeter(const HandMeter &other) = delete;
    HandMeter& operator = (const HandMeter & other) = delete;

    void setSizeAndPos(const int size, const int pos);
};

/*
 * Class: Element
 *
 * Elements are various TUI components that are rendered (drawn) onto Canvases. Element is the base
 * class for all specialized elements (such as Label, Card, Button, etc) that provides the methods update
 * and render. Elements should not store information within them other than the string to print onto the canvas
 * and should only have updates done to that state.
 *
 * Element in its base class acts as an unchangeable string that represents the Element's body.
 */
/*
class Element {
public:
    Element();
    Element(const Canvas* defaultCanvas, int locX, int locY, int attribute);
    Element(const Canvas* defaultCanvas, int locX, int locY, char** body, int cols, int rows, int attribute);
    virtual ~Element();

    // No Copying Right Now...
    Element(const Element &other) = delete;
    Element& operator = (const Element & other) = delete;

    void setAttribute(int attr);
    void clearElement();
    //virtual void move(int x, int y);
    //virtual void resize(int cols, int rows);
    virtual void render();                   // Render onto default canvas
    virtual void renderOnto(const Canvas&);  // Render onto specified canvas
    void setBody(char **newBody, int cols, int rows);
    void setCanvas(const Canvas*);

private:

    void deleteBody();  // DO NOT CALL EXPLICITLY

    char** body;
    const Canvas* defaultCanvas;
    int attribute;
    int x;
    int y;
    int cols;
    int rows;

};

class Label : public Element {
public:
    Label(const Canvas* defaultCanvas, int locX, int locY, int totalLength, int attr);
    Label(const Canvas* defaultCanvas, int locX, int locY, int totalLength);
    Label(const Label &other) = delete;
    Label& operator = (const Label & other) = delete;
    ~Label() override = default;

    void setText(const char* text, int attr=-1);

private:

    const int totalLength;

};

// Ex: [-|---]
class HandMeter : public Label {
public:
    HandMeter(const Canvas* defaultCanvas, int locX, int locY);
    HandMeter(const HandMeter &other) = delete;
    HandMeter& operator = (const HandMeter & other) = delete;
    ~HandMeter() override = default;

    void setSizeAndPos(int size, int pos);
};

class DeckMeter : public Label {
public:
    DeckMeter(const Canvas* defaultCanvas, int locX, int locY, int deckSize);
    DeckMeter(const DeckMeter &other) = delete;
    DeckMeter& operator = (const DeckMeter & other) = delete;
    ~DeckMeter() override = default;

    void render() override;
    void renderOnto(const Canvas&) override;
    void setDeckSize(int size);

private:

    const int deckSize;

};
*/

#endif //UNO_ONLINE_MULTIPLAYER_UI_ELEMENTS_H
