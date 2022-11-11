#include <SDL.h>
#include "Label.h"
#include "Session.h"
#include "Button.h"

using namespace fruitwork;

int main(int argc, char **argv)
{
    Session session;

    Label *label = Label::getInstance(10, 10, 200, 100, "Salmon");

    Button *button = Button::getInstance(10, 120, 200, 100, "Click me");

    session.add_component(label);
    session.add_component(button);
    label->setText("Salmon... TWO");

    session.run();


    return 0;
}
