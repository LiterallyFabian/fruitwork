#include "TestSceneHierarchy.h"
#include "Button.h"
#include "System.h"
#include "Label.h"
#include "TestSceneIndex.h"
#include "Main.h"
#include "ResourceManager.h"
#include "Rectangle.h"

using namespace fruitwork;

namespace fruitwork
{
    bool TestSceneHierarchy::enter()
    {
        Label *titleText = Label::getInstance(0, 25, 1200, 900, "Visual tests::Parent/Child");
        titleText->setAlignment(Label::Alignment::CENTER);
        titleText->setFontSize(100);

        // test scene button
        Button *returnButton = Button::getInstance(10, 842, 240, 48, "Back to index");
        returnButton->registerCallback([](Button *src)
                                       {
                                           sys.setNextScene(TestSceneIndex::getInstance());
                                       });

        Label *controlLabel = Label::getInstance(260, 842, 400, 48, "A to attach/detach");
        controlLabel->setAlignment(Label::Alignment::LEFT);
        controlLabel->setFontSize(20);

        parent = Sprite::getInstance(20, 200, 392, 348, ResourceManager::getTexturePath("pippi-0.png"), true);
        child = Sprite::getInstance(20, 400, 392, 348, ResourceManager::getTexturePath("pippi-1.png"), true);

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
//        addComponent(controlLabel);
//        addComponent(parent, -1);
//        addComponent(child, -1);

        Rectangle *emptyParent = Rectangle::getInstance(0, 0, 100, 200, {0, 0, 0, 30});
        emptyParent->setAnchor(Anchor::CENTER);

        Rectangle *topCenterChild = Rectangle::getInstance(0, 0, 50, 150, {159, 238, 149, 255});
        topCenterChild->setAnchor(Anchor::TOP_CENTER);
        emptyParent->addChild(topCenterChild);

        Rectangle *bottomLeftChild = Rectangle::getInstance(0, 0, 75, 50, {221, 110, 110, 255});
        bottomLeftChild->setAnchor(Anchor::BOTTOM_LEFT);
        emptyParent->addChild(bottomLeftChild);

        Rectangle *blueCenterChildChild = Rectangle::getInstance(0, 0, 25, 25, {110, 221, 213, 255});
        blueCenterChildChild->setAnchor(Anchor::CENTER);
        bottomLeftChild->addChild(blueCenterChildChild);

        addComponent(emptyParent, -2);
        addComponent(topCenterChild, -2);
        addComponent(bottomLeftChild, -2);
        addComponent(blueCenterChildChild, -2);
        
        return true;
    }

    bool TestSceneHierarchy::exit()
    {
        bool success = true;
        SDL_Log("Exiting TestSceneHierarchy...");

        for (auto &c : components)
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