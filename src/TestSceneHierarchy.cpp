#include "TestSceneHierarchy.h"
#include "Button.h"
#include "System.h"
#include "Label.h"
#include "TestSceneIndex.h"
#include "Main.h"
#include "ResourceManager.h"

namespace fruitwork
{
    bool fruitwork::TestSceneHierarchy::enter()
    {
        fruitwork::Label *titleText = fruitwork::Label::getInstance(0, 25, 1200, 900, "Visual tests::Parent/Child");
        titleText->setAlignment(fruitwork::Label::Alignment::CENTER);
        titleText->setFontSize(100);

        // test scene button
        fruitwork::Button *returnButton = fruitwork::Button::getInstance(10, 842, 240, 48, "Back to index");
        returnButton->registerCallback([](fruitwork::Button *src)
                                       {
                                           fruitwork::sys.setNextScene(fruitwork::TestSceneIndex::getInstance());
                                       });

        fruitwork::Label *controlLabel = fruitwork::Label::getInstance(260, 842, 400, 48, "A to attach/detach");
        controlLabel->setAlignment(fruitwork::Label::Alignment::LEFT);
        controlLabel->setFontSize(20);

        parent = fruitwork::Sprite::getInstance(20, 200, 392, 348, fruitwork::ResourceManager::getTexturePath("pippi-0.png"), true);
        child = fruitwork::Sprite::getInstance(20, 400, 392, 348, fruitwork::ResourceManager::getTexturePath("pippi-1.png"), true);

        yuzu::ses.registerKeyboardEvent(SDLK_a, [this]()
        {
            if (attached)
            {
                parent->removeChild(child);
                attached = false;
            }
            else
            {
                parent->addChild(child);
                attached = true;
            }
        });

        addComponent(titleText);
        addComponent(returnButton);
        addComponent(controlLabel);
        addComponent(parent, -1);
        addComponent(child, -1);
        return true;
    }

    bool fruitwork::TestSceneHierarchy::exit()
    {
        bool success = true;
        SDL_Log("Exiting TestSceneHierarchy...");

        for (auto &c: components)
            removeComponent(c, true);

        yuzu::ses.deregisterKeyboardEvent(SDLK_a);

        return success;
    }

    void TestSceneHierarchy::update()
    {
        int x, y;
        SDL_GetMouseState(&x, &y);

        parent->setRect({x - 392 / 2, y - 348 / 2, 392, 348});
    }

    TestSceneHierarchy TestSceneHierarchy::instance;

} // fruitwork