#include <SDL.h>
#include <iostream>
#include "Label.h"
#include "Session.h"
#include "Button.h"

using namespace fruitwork;

int main(int argc, char **argv)
{
    Session session;

    Label *label = Label::getInstance(10, 10, 200, 100, "Salmon");

    Button *button = Button::getInstance(10, 120, 200, 100, "Click me");

    button->registerCallback([](Button *source)
                             {
                                 std::cout << "Hello world from " << source->getText() << std::endl;
                             });

    session.add_component(label);
    session.add_component(button);
    label->setText("Salmon... TWO");

    session.run();


    return 0;
}
