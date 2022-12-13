#include "TestSceneIndex.h"
#include "Label.h"
#include "Button.h"
#include "TestScene.h"

namespace fruitwork
{
    bool fruitwork::TestSceneIndex::enter()
    {
        fruitwork::Label *titleText = fruitwork::Label::getInstance(0, 25, 1200, 900, "fruitwork::Visual tests");

        fruitwork::Button *buttonButtonTests = fruitwork::Button::getInstance(50, 200, 240, 48, "Small button");
        buttonButtonTests->registerCallback([](fruitwork::Button *src)
                                            {
                                                fruitwork::sys.setNextScene(TestScene::getInstance());
                                            });

        addComponent(titleText);
        addComponent(buttonButtonTests);

        return true;
    }

    bool fruitwork::TestSceneIndex::exit()
    {
        bool success = true;
        SDL_Log("Exiting TestSceneIndex...");

        for (auto &c: components)
        {
            delete c;
        }

        return success;
    }

    TestSceneIndex TestSceneIndex::instance;

} // fruitwork