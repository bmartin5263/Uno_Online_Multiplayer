#include <panel.h>
#include <ncurses.h>
#include <menu.h>
#include <cstdlib>
#include <form.h>
#include "ui.h"

int main()
{
    UI* u = new UI();
    u->run();
    delete u;
}