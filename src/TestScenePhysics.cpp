#include "TestScenePhysics.h"
#include "System.h"
#include "Label.h"
#include "Button.h"
#include "TestSceneIndex.h"
#include "Sprite.h"
#include "ResourceManager.h"

namespace fruitwork
{
    bool TestScenePhysics::enter()
    {
        fruitwork::Label *titleText = fruitwork::Label::getInstance(0, 25, 1200, 900, "Visual tests::Physics");
        titleText->setAlignment(fruitwork::Label::Alignment::CENTER);
        titleText->setFontSize(100);

        // test scene button
        fruitwork::Button *returnButton = fruitwork::Button::getInstance(10, 842, 240, 48, "Back to index");
        returnButton->registerCallback([](fruitwork::Button *src)
                                       {
                                           fruitwork::sys.setNextScene(fruitwork::TestSceneIndex::getInstance());
                                       });
        returnButton->setColor({255, 255, 255, 128});
        returnButton->setTextColor({0, 0, 0, 128});

        sprite = fruitwork::Sprite::getInstance(20, 200, 392, 348, fruitwork::ResourceManager::getTexturePath("pippi-0.png"), true);
        auto *body = new PhysicsBody(sprite->getRect());
        body->setScreenCollision(true);
        body->setObjCollision(true);
        sprite->setPhysicsBody(body);

        fruitwork::Sprite *sprite2 = fruitwork::Sprite::getInstance(600, 200, 48, 48, fruitwork::ResourceManager::getTexturePath("fruit-orange.png"), true);
        auto *body2 = new PhysicsBody(sprite2->getRect());
        body2->setScreenCollision(true);
        body2->setObjCollision(true);
        sprite2->setPhysicsBody(body2);
        sprite2->setColorMod({255, 153, 51, 255});

        spriteMeta = fruitwork::Label::getInstance(260, 842, 400, 48, "0,0");
        spriteMeta->setAlignment(fruitwork::Label::Alignment::LEFT);
        spriteMeta->setFontSize(20);

#pragma region Buttons
        fruitwork::Button *forceButton1 = fruitwork::Button::getInstance(20, 600, 240, 48, "Apply 0,-50");
        forceButton1->registerCallback([this](fruitwork::Button *src)
                                       {
                                           sprite->getPhysicsBody()->addForce(0, -50);
                                       });

        fruitwork::Button *forceButton2 = fruitwork::Button::getInstance(262, 600, 240, 48, "Apply 50,0");
        forceButton2->registerCallback([this](fruitwork::Button *src)
                                       {
                                           sprite->getPhysicsBody()->addForce(50, 0);
                                       });

        fruitwork::Button *forceButton3 = fruitwork::Button::getInstance(504, 600, 240, 48, "Apply 0,50");
        forceButton3->registerCallback([this](fruitwork::Button *src)
                                       {
                                           sprite->getPhysicsBody()->addForce(0, 50);
                                       });

        fruitwork::Button *forceButton4 = fruitwork::Button::getInstance(746, 600, 240, 48, "Apply -50,0");
        forceButton4->registerCallback([this](fruitwork::Button *src)
                                       {
                                           sprite->getPhysicsBody()->addForce(-50, 0);
                                       });

        fruitwork::Button *forceButton5 = fruitwork::Button::getInstance(988, 600, 240, 48, "Apply 500,-500");
        forceButton5->registerCallback([this](fruitwork::Button *src)
                                       {
                                           sprite->getPhysicsBody()->addForce(500, -500);
                                       });

        fruitwork::Button *setGravityButton1 = fruitwork::Button::getInstance(20, 650, 240, 48, "Set gravity 1x");
        setGravityButton1->registerCallback([this](fruitwork::Button *src)
                                            {
                                                sprite->getPhysicsBody()->setGravity(1);
                                            });

        fruitwork::Button *setGravityButton2 = fruitwork::Button::getInstance(262, 650, 240, 48, "Set gravity 0.5x");
        setGravityButton2->registerCallback([this](fruitwork::Button *src)
                                            {
                                                sprite->getPhysicsBody()->setGravity(0.5);
                                            });

        fruitwork::Button *setGravityButton3 = fruitwork::Button::getInstance(504, 650, 240, 48, "Set gravity 2x");
        setGravityButton3->registerCallback([this](fruitwork::Button *src)
                                            {
                                                sprite->getPhysicsBody()->setGravity(2);
                                            });

        fruitwork::Button *removeGravityButton = fruitwork::Button::getInstance(746, 650, 240, 48, "Remove gravity");
        removeGravityButton->registerCallback([this](fruitwork::Button *src)
                                              {
                                                  sprite->getPhysicsBody()->setGravity(0);
                                              });

        fruitwork::Button *setFrictionButton1 = fruitwork::Button::getInstance(20, 700, 240, 48, "Set friction 1%");
        setFrictionButton1->registerCallback([this](fruitwork::Button *src)
                                             {
                                                 sprite->getPhysicsBody()->setFriction(0.01f);
                                             });

        fruitwork::Button *setFrictionButton2 = fruitwork::Button::getInstance(262, 700, 240, 48, "Set friction 50%");
        setFrictionButton2->registerCallback([this](fruitwork::Button *src)
                                             {
                                                 sprite->getPhysicsBody()->setFriction(0.5f);
                                             });

        fruitwork::Button *setFrictionButton3 = fruitwork::Button::getInstance(504, 700, 240, 48, "Set friction 200%");
        setFrictionButton3->registerCallback([this](fruitwork::Button *src)
                                             {
                                                 sprite->getPhysicsBody()->setFriction(2.0f);
                                             });

        fruitwork::Button *removeFrictionButton = fruitwork::Button::getInstance(746, 700, 240, 48, "Set friction 0%");
        removeFrictionButton->registerCallback([this](fruitwork::Button *src)
                                               {
                                                   sprite->getPhysicsBody()->setFriction(0);
                                               });

        fruitwork::Button *resetButton = fruitwork::Button::getInstance(20, 775, 240, 48, "Reset");
        resetButton->registerCallback([](fruitwork::Button *src)
                                      {
                                          fruitwork::sys.setNextScene(fruitwork::TestScenePhysics::getInstance());
                                      });
        resetButton->setColor({255, 0, 255, 128});

#pragma endregion

        addComponent(titleText);
        addComponent(returnButton);
        addComponent(spriteMeta);
        addComponent(sprite, -1);
        addComponent(sprite2, -1);
        addComponent(forceButton1);
        addComponent(forceButton2);
        addComponent(forceButton3);
        addComponent(forceButton4);
        addComponent(forceButton5);
        addComponent(setGravityButton1);
        addComponent(setGravityButton2);
        addComponent(setGravityButton3);
        addComponent(removeGravityButton);
        addComponent(setFrictionButton1);
        addComponent(setFrictionButton2);
        addComponent(setFrictionButton3);
        addComponent(removeFrictionButton);
        addComponent(resetButton);

        return true;
    }

    bool TestScenePhysics::exit()
    {
        bool success = true;
        SDL_Log("Exiting TestScenePhysics...");

        for (auto &c: components)
            removeComponent(c, true);

        return success;
    }

    void TestScenePhysics::update()
    {
        spriteMeta->setText("pos: " + std::to_string(sprite->getRect().x) + "," + std::to_string(sprite->getRect().y) +
                            "\nvel: " + std::to_string(sprite->getPhysicsBody()->getVelocity().x) + "," +
                            std::to_string(sprite->getPhysicsBody()->getVelocity().y));
    }

    TestScenePhysics TestScenePhysics::instance;

} // fruitwork