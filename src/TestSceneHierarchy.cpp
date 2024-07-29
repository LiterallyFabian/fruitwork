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
        titleText->setAnchorAndPivot(Anchor::TOP_STRETCH);
        titleText->setAlignment(Label::Alignment::CENTER);
        titleText->setFontSize(90);

        Button *returnButton = Button::getInstance(16, 16, 240, 48, "Back to index");
        returnButton->setAnchorAndPivot(Anchor::BOTTOM_LEFT);
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

#pragma region rectangles
        Rectangle *emptyParent = Rectangle::getInstance(-200, 0, 100, 200, {0, 0, 0, 30});
        emptyParent->setAnchorAndPivot(Anchor::CENTER);

        Label *emptyParentLabel = Label::getInstance(0, 50, 160, 30, "Positions");
        emptyParentLabel->setAnchorAndPivot(Anchor::TOP_CENTER);
        emptyParentLabel->setAlignment(Label::Alignment::CENTER);
        emptyParent->addChild(emptyParentLabel);

        Rectangle *topLeftChild = Rectangle::getInstance(30, 5, 50, 80, {159, 238, 149, 255});
        topLeftChild->setAnchorAndPivot(Anchor::TOP_LEFT);
        emptyParent->addChild(topLeftChild);

        Rectangle *topCenterChild = Rectangle::getInstance(10, -10, 25, 50, {221, 211, 110, 255});
        topCenterChild->setAnchorAndPivot(Anchor::TOP_CENTER);
        emptyParent->addChild(topCenterChild);

        Rectangle *topRightChild = Rectangle::getInstance(10, -20, 50, 25, {221, 154, 110, 255});
        topRightChild->setAnchorAndPivot(Anchor::TOP_RIGHT);
        emptyParent->addChild(topRightChild);

        Rectangle *centerLeftChild = Rectangle::getInstance(-20, -10, 20, 20, {110, 221, 213, 255});
        centerLeftChild->setAnchorAndPivot(Anchor::CENTER_LEFT);
        emptyParent->addChild(centerLeftChild);

        Rectangle *centerCenterChild = Rectangle::getInstance(40, -20, 40, 40, {221, 110, 212, 255});
        centerCenterChild->setAnchorAndPivot(Anchor::CENTER);
        emptyParent->addChild(centerCenterChild);

        Rectangle *centerRightChild = Rectangle::getInstance(-10, 20, 20, 20, {255, 255, 255, 255});
        centerRightChild->setAnchorAndPivot(Anchor::CENTER_RIGHT);
        emptyParent->addChild(centerRightChild);

        Rectangle *bottomLeftChild = Rectangle::getInstance(5, 5, 75, 50, {221, 110, 110, 255});
        bottomLeftChild->setAnchorAndPivot(Anchor::BOTTOM_LEFT);
        emptyParent->addChild(bottomLeftChild);

        Rectangle *centerChildChild = Rectangle::getInstance(0, 0, 25, 25, {110, 221, 213, 255});
        centerChildChild->setAnchorAndPivot(Anchor::CENTER);
        bottomLeftChild->addChild(centerChildChild);

        Rectangle *bottomCenterChild = Rectangle::getInstance(-20, 20, 30, 15, {166, 110, 221, 255});
        bottomCenterChild->setAnchorAndPivot(Anchor::BOTTOM_CENTER);
        emptyParent->addChild(bottomCenterChild);

        Rectangle *bottomRightChild = Rectangle::getInstance(-5, -5, 30, 15, {110, 126, 221, 255});
        bottomRightChild->setAnchorAndPivot(Anchor::BOTTOM_RIGHT);
        emptyParent->addChild(bottomRightChild);

        addComponent(emptyParent, -10);
        addComponent(emptyParentLabel, -2);
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

        // Stretch
        Rectangle *stretchParent = Rectangle::getInstance(0, 0, 100, 200, {0, 0, 0, 30});
        stretchParent->setAnchorAndPivot(Anchor::CENTER);

        Label *stretchParentLabel = Label::getInstance(0, 50, 160, 30, "Stretch");
        stretchParentLabel->setAnchorAndPivot(Anchor::TOP_CENTER);
        stretchParentLabel->setAlignment(Label::Alignment::CENTER);
        stretchParent->addChild(stretchParentLabel);

        Rectangle *topStretchChild = Rectangle::getInstance(10, -10, 5, 20, {159, 238, 149, 255});
        topStretchChild->setAnchorAndPivot(Anchor::TOP_STRETCH);
        stretchParent->addChild(topStretchChild);

        Rectangle *centerStretchChild = Rectangle::getInstance(45, 30, 10, 20, {221, 110, 110, 255});
        centerStretchChild->setAnchorAndPivot(Anchor::CENTER_STRETCH);
        stretchParent->addChild(centerStretchChild);

        Rectangle *bottomStretchChild = Rectangle::getInstance(10, 10, 30, 50, {221, 211, 110, 255});
        bottomStretchChild->setAnchorAndPivot(Anchor::BOTTOM_STRETCH);
        stretchParent->addChild(bottomStretchChild);

        Rectangle *stretchLeftChild = Rectangle::getInstance(10, 50, 30, 5, {110, 221, 213, 255});
        stretchLeftChild->setAnchorAndPivot(Anchor::STRETCH_LEFT);
        stretchParent->addChild(stretchLeftChild);

        Rectangle *stretchRightChild = Rectangle::getInstance(-10, 50, 15, 20, {221, 110, 212, 255});
        stretchRightChild->setAnchorAndPivot(Anchor::STRETCH_RIGHT);
        stretchParent->addChild(stretchRightChild);

        Rectangle *stretchCenterChild = Rectangle::getInstance(15, 5, 10, 70, {255, 255, 255, 255});
        stretchCenterChild->setAnchorAndPivot(Anchor::STRETCH_CENTER);
        stretchParent->addChild(stretchCenterChild);

        addComponent(stretchParent, -10);
        addComponent(stretchParentLabel, -2);
        addComponent(topStretchChild, -2);
        addComponent(centerStretchChild, -2);
        addComponent(bottomStretchChild, -2);
        addComponent(stretchLeftChild, -3);
        addComponent(stretchRightChild, -3);
        addComponent(stretchCenterChild, -3);

        // Rotations
        Rectangle *rotationParent = Rectangle::getInstance(200, 0, 100, 200, {0, 0, 0, 30});
        rotationParent->setAnchorAndPivot(Anchor::CENTER);
        rotationParent->setAngle(45);

        Label *rotationParentLabel = Label::getInstance(0, 50, 160, 30, "Rotations");
        rotationParentLabel->setAnchorAndPivot(Anchor::TOP_CENTER);
        rotationParentLabel->setAlignment(Label::Alignment::CENTER);
        rotationParent->addChild(rotationParentLabel);

        Rectangle *rotationStretchChild = Rectangle::getInstance(10, 10, 10, 10, {159, 238, 149, 255});
        rotationStretchChild->setAnchorAndPivot(Anchor::STRETCH);
        rotationParent->addChild(rotationStretchChild);

        Rectangle *rotationTopLeftChild = Rectangle::getInstance(-5, -15, 30, 50, {110, 221, 213, 255});
        rotationTopLeftChild->setAnchorAndPivot(Anchor::TOP_LEFT);
        rotationParent->addChild(rotationTopLeftChild);

        addComponent(rotationParent, -10);
        addComponent(rotationParentLabel, -2);
        addComponent(rotationStretchChild, -2);
        addComponent(rotationTopLeftChild, -2);
#pragma endregion

#pragma region buttons
        Rectangle *buttonParent = Rectangle::getInstance(0, -250, 400, 200, {0, 0, 0, 30});
        buttonParent->setAnchorAndPivot(Anchor::CENTER);

        Button *centerButton = Button::getInstance(0, 0, 100, 100, "A long button title!");
        centerButton->setAnchorAndPivot(Anchor::CENTER);
        buttonParent->addChild(centerButton);

        Button *stretchButton = Button::getInstance(5, -5, 5, 30, "Stretch!");
        stretchButton->setAnchorAndPivot(Anchor::TOP_STRETCH);
        buttonParent->addChild(stretchButton);

        Button *nestedButton = Button::getInstance(0, 0, 50, 0, "nested");
        nestedButton->setAnchorAndPivot(Anchor::STRETCH_RIGHT);
        stretchButton->addChild(nestedButton);

        addComponent(buttonParent, -10);
        addComponent(centerButton, -2);
        addComponent(stretchButton, -2);
        addComponent(nestedButton, -2);
#pragma endregion

#pragma region sprites
        Sprite *centerRightSprite = Sprite::getInstance(-20, 0, 250, 250, ResourceManager::getTexturePath("jerafina.png"), true);
        centerRightSprite->setAnchorAndPivot(Anchor::CENTER_RIGHT);

        Sprite *centerRightSpriteRotated = Sprite::getInstance(-20, 0, 250, 250, ResourceManager::getTexturePath("jerafina.png"), true);
        centerRightSpriteRotated->setAnchorAndPivot(Anchor::CENTER_RIGHT);
        centerRightSpriteRotated->setAngle(45);

        addComponent(centerRightSprite, -10);
        addComponent(centerRightSpriteRotated, -10);

#pragma endregion

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