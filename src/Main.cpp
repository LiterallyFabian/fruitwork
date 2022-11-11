#include <SDL.h>
#include "Label.h"
#include "Session.h"

using namespace fruitwork;

int main(int argc, char **argv)
{
    Session session;

    Label *label = Label::getInstance(10, 10, 200, 100, "Salmon");

    session.add_component(label);
    session.run();

    return 0;
}
