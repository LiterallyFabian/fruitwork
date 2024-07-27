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
        Label *titleText = Label::getInstance(15, -25, 15, 200, "Visual tests::Parent/Child");
        titleText->setAnchor(Anchor::TOP_STRETCH);
        titleText->setAlignment(Label::Alignment::CENTER);
        titleText->setFontSize(90);

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

        Rectangle *emptyParent = Rectangle::getInstance(-100, 0, 100, 200, {0, 0, 0, 30});
        emptyParent->setAnchor(Anchor::CENTER);

        Rectangle *topLeftChild = Rectangle::getInstance(30, 5, 50, 80, {159, 238, 149, 255});
        topLeftChild->setAnchor(Anchor::TOP_LEFT);
        emptyParent->addChild(topLeftChild);

        Rectangle *topCenterChild = Rectangle::getInstance(10, -10, 25, 50, {221, 211, 110, 255});
        topCenterChild->setAnchor(Anchor::TOP_CENTER);
        emptyParent->addChild(topCenterChild);

        Rectangle *topRightChild = Rectangle::getInstance(10, -20, 50, 25, {221, 154, 110, 255});
        topRightChild->setAnchor(Anchor::TOP_RIGHT);
        emptyParent->addChild(topRightChild);

        Rectangle *centerLeftChild = Rectangle::getInstance(-20, -10, 20, 20, {110, 221, 213, 255});
        centerLeftChild->setAnchor(Anchor::CENTER_LEFT);
        emptyParent->addChild(centerLeftChild);

        Rectangle *centerCenterChild = Rectangle::getInstance(40, -20, 40, 40, {221, 110, 212, 255});
        centerCenterChild->setAnchor(Anchor::CENTER);
        emptyParent->addChild(centerCenterChild);

        Rectangle *centerRightChild = Rectangle::getInstance(-10, 20, 20, 20, {255, 255, 255, 255});
        centerRightChild->setAnchor(Anchor::CENTER_RIGHT);
        emptyParent->addChild(centerRightChild);

        Rectangle *bottomLeftChild = Rectangle::getInstance(5, 5, 75, 50, {221, 110, 110, 255});
        bottomLeftChild->setAnchor(Anchor::BOTTOM_LEFT);
        emptyParent->addChild(bottomLeftChild);

        Rectangle *centerChildChild = Rectangle::getInstance(0, 0, 25, 25, {110, 221, 213, 255});
        centerChildChild->setAnchor(Anchor::CENTER);
        bottomLeftChild->addChild(centerChildChild);

        Rectangle *bottomCenterChild = Rectangle::getInstance(-20, 20, 30, 15, {166, 110, 221, 255});
        bottomCenterChild->setAnchor(Anchor::BOTTOM_CENTER);
        emptyParent->addChild(bottomCenterChild);

        Rectangle *bottomRightChild = Rectangle::getInstance(-5, -5, 30, 15, {110, 126, 221, 255});
        bottomRightChild->setAnchor(Anchor::BOTTOM_RIGHT);
        emptyParent->addChild(bottomRightChild);

        // Stretch
        Rectangle *stretchParent = Rectangle::getInstance(100, 0, 100, 200, {0, 0, 0, 30});
        stretchParent->setAnchor(Anchor::CENTER);

        Rectangle *topStretchChild = Rectangle::getInstance(5, -10, 5, 20, {159, 238, 149, 255});
        topStretchChild->setAnchor(Anchor::TOP_STRETCH);
        stretchParent->addChild(topStretchChild);

        Rectangle *centerStretchChild = Rectangle::getInstance(10, 30, 10, 20, {221, 110, 110, 255});
        centerStretchChild->setAnchor(Anchor::CENTER_STRETCH);
        stretchParent->addChild(centerStretchChild);

        Rectangle *bottomStretchChild = Rectangle::getInstance(10, 10, 30, 50, {221, 211, 110, 255});
        bottomStretchChild->setAnchor(Anchor::BOTTOM_STRETCH);
        stretchParent->addChild(bottomStretchChild);

        Rectangle *stretchLeftChild = Rectangle::getInstance(5, 5, 30, 5, {110, 221, 213, 255});
        stretchLeftChild->setAnchor(Anchor::STRETCH_LEFT);
        stretchParent->addChild(stretchLeftChild);

        Rectangle *stretchRightChild = Rectangle::getInstance(-10, 50, 15, 50, {221, 110, 212, 255});
        stretchRightChild->setAnchor(Anchor::STRETCH_RIGHT);
        stretchParent->addChild(stretchRightChild);

        Rectangle *stretchCenterChild = Rectangle::getInstance(5, 5, 5, 5, {255, 255, 255, 255});
        stretchCenterChild->setAnchor(Anchor::STRETCH_CENTER);
        stretchParent->addChild(stretchCenterChild);

        addComponent(emptyParent, -10);
        addComponent(topLeftChild, -2);
        addComponent(topCenterChild, -2);
        addComponent(topRightChild, -2);
        addComponent(centerLeftChild, -2);
        addComponent(centerCenterChild, -2);
        addComponent(centerRightChild, -2);
        addComponent(bottomLeftChild, -2);
        addComponent(centerChildChild, -2);
        addComponent(bottomCenterChild, -2);
        addComponent(bottomRightChild, -2);

        addComponent(stretchParent, -10);
        addComponent(topStretchChild, -2);
        addComponent(centerStretchChild, -2);
        addComponent(bottomStretchChild, -2);
        addComponent(stretchLeftChild, -3);
        addComponent(stretchRightChild, -3);
        addComponent(stretchCenterChild, -3);

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