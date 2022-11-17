#include "ExitScene.h"

namespace fruitwork
{
    ExitScene *ExitScene::get_instance()
    {
        return &instance;
    }

    bool ExitScene::enter() { return true; }

    bool ExitScene::exit() { return true; }

    void ExitScene::handleEvent(SDL_Event &e) {}

    void ExitScene::update() {}

    void ExitScene::draw() {}

    ExitScene::ExitScene() = default;

    ExitScene ExitScene::instance;

} // fruitwork