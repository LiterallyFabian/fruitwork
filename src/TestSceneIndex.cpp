#include "TestSceneIndex.h"
#include "Label.h"
#include "Button.h"
#include "TestScene.h"
#include "TestSceneCollision.h"
#include "TestScenePhysics.h"
#include "TestSceneHierarchy.h"

namespace fruitwork
{
    bool fruitwork::TestSceneIndex::enter()
    {
        fruitwork::Label *titleText = fruitwork::Label::getInstance(0, 25, 1200, 900, "fruitwork::Visual tests");
        titleText->setAlignment(fruitwork::Label::Alignment::CENTER);
        titleText->setFontSize(100);

        fruitwork::Button *buttonButtonTests = fruitwork::Button::getInstance(50, 200, 240, 48, "General tests");
        buttonButtonTests->registerCallback([](fruitwork::Button *src)
                                            {
                                                fruitwork::sys.setNextScene(TestScene::getInstance());
                                            });

        fruitwork::Button *buttonCollisionTests = fruitwork::Button::getInstance(50, 300, 240, 48, "Collision tests");
        buttonCollisionTests->registerCallback([](fruitwork::Button *src)
                                               {
                                                   fruitwork::sys.setNextScene(TestSceneCollision::getInstance());
                                               });

        fruitwork::Button *buttonPhysicsTests = fruitwork::Button::getInstance(50, 400, 240, 48, "Physics tests");
        buttonPhysicsTests->registerCallback([](fruitwork::Button *src)
                                             {
                                                 fruitwork::sys.setNextScene(TestScenePhysics::getInstance());
                                             });

        fruitwork::Button *buttonHierarchyTests = fruitwork::Button::getInstance(50, 500, 240, 48, "Hierarchy tests");
        buttonHierarchyTests->registerCallback([](fruitwork::Button *src)
                                               {
                                                   fruitwork::sys.setNextScene(TestSceneHierarchy::getInstance());
                                               });

        addComponent(titleText);
        addComponent(buttonButtonTests);
        addComponent(buttonCollisionTests);
        addComponent(buttonPhysicsTests);
        addComponent(buttonHierarchyTests);

        return true;
    }

    bool fruitwork::TestSceneIndex::exit()
    {
        bool success = true;
        SDL_Log("Exiting TestSceneIndex...");

        for (auto &c: components)
            removeComponent(c, true);

        return success;
    }

    TestSceneIndex TestSceneIndex::instance;

} // fruitwork