#include <iostream>
#include <SDL_image.h>
#include "TestScene.h"
#include "Label.h"
#include "Button.h"
#include "InputField.h"
#include "Sprite.h"
#include "ResponsiveSprite.h"
#include "AnimatedSprite.h"
#include "ResourceManager.h"
#include "ImageButton.h"
#include "TestSceneIndex.h"

namespace fruitwork
{
    fruitwork::Label *title = nullptr;
    Sprite *responsiveSprite2 = ResponsiveSprite::getInstance(800, 650, 128, 256, ResourceManager::getTexturePath("jerafina.png"));

    bool TestScene::enter()
    {
        title = fruitwork::Label::getInstance(0, 25, 1200, 900, "Visual tests::General");

        bool success = true;
        SDL_Log("Entering TestScene...");

        title->setAlignment(fruitwork::Label::Alignment::CENTER);
        title->setFontSize(100);

        // small button
        fruitwork::Button *smallButton = fruitwork::Button::getInstance(50, 200, 240, 48, "Small button");
        smallButton->setColor({128, 0, 0, 255});

        // small button with a long text
        fruitwork::Button *smallButton2 = fruitwork::Button::getInstance(50, 300, 240, 48, "Small button with a long text");

        // medium button
        fruitwork::Button *mediumButton = fruitwork::Button::getInstance(50, 400, 390, 48, "Medium button");
        mediumButton->setColor({0, 128, 0, 255});
        mediumButton->setTextColor({128, 255, 56, 255});

        // large button
        fruitwork::Button *largeButton = fruitwork::Button::getInstance(50, 500, 540, 48, "Large button with a callback");
        largeButton->registerCallback([](fruitwork::Button *src)
                                      {
                                          title->setText("Callback called! " + std::to_string(rand() % 10000));
                                      });

        // tall button
        fruitwork::Button *tallButton = fruitwork::Button::getInstance(50, 600, 240, 96, "Tall button");

        // normal input field
        fruitwork::InputField *inputField = fruitwork::InputField::getInstance(650, 200, 390, 48, "Enter your name...");

        // password input field
        fruitwork::InputField *passwordInputField = fruitwork::InputField::getInstance(650, 300, 390, 48, "Enter your password...",
                                                                                       fruitwork::InputField::InputType::PASSWORD);

        // numeric input field
        fruitwork::InputField *numericInputField = fruitwork::InputField::getInstance(650, 400, 390, 48, "Enter your age...",
                                                                                      fruitwork::InputField::InputType::NUMERIC);

        Label *leftAnchoredLabel = Label::getInstance(0, 850, 1200, 900, "Left anchored label");
        leftAnchoredLabel->setAlignment(Label::Alignment::LEFT);

        Label *centerAnchoredLabel = Label::getInstance(0, 850, 1200, 900, "Center anchored label, new font");
        centerAnchoredLabel->setAlignment(Label::Alignment::CENTER);
        centerAnchoredLabel->setFontPath(ResourceManager::getFontPath("KGRedHands.ttf"));

        Label *rightAnchoredLabel = Label::getInstance(0, 850, 1200, 900, "Right anchored tiny label");
        rightAnchoredLabel->setAlignment(Label::Alignment::RIGHT);
        rightAnchoredLabel->setFontSize(12);

        // sprites that are too wide
        Sprite *sprite = Sprite::getInstance(650, 500, 256, 128, ResourceManager::getTexturePath("jerafina.png"));

        // not owner of the texture
        SDL_Texture *texture = IMG_LoadTexture(sys.getRenderer(), ResourceManager::getTexturePath("button-middle.png").c_str());
        Sprite *responsiveSprite = ResponsiveSprite::getInstance(650, 650, 256, 128, texture);

        // sprites that are too tall
        Sprite *sprite2 = Sprite::getInstance(950, 500, 128, 256, ResourceManager::getTexturePath("jerafina.png"));
        responsiveSprite2->setTexture(ResourceManager::getTexturePath("jerafina.png"));
        responsiveSprite2->setColorMod({255, 255, 0, 255});
        responsiveSprite2->setFlip(SDL_FLIP_HORIZONTAL);


        ImageButton *imageButton = ImageButton::getInstance(450, 200, 128, 128, ResourceManager::getTexturePath("fruit-catcher-kiai.png"));
        imageButton->registerCallback([](fruitwork::Button *src)
                                      {
                                          title->setText("Image called! " + std::to_string(rand() % 10000));
                                      });
        imageButton->setFlip(SDL_FLIP_VERTICAL);

        ImageButton *imageButton2 = ImageButton::getInstance(450, 200 + 128, 256, 128, ResourceManager::getTexturePath("jerafina.png"));
        imageButton2->registerCallback([](fruitwork::Button *src)
                                       {
                                           title->setText("Image called! " + std::to_string(rand() % 10000));
                                           // set sprite to fruit-apple.png or fruit-banana.png
                                           if (rand() % 2 == 0)
                                           {
                                               responsiveSprite2->setTexture(ResourceManager::getTexturePath("fruit-apple.png"));
                                           }
                                           else
                                           {
                                               responsiveSprite2->setTexture(ResourceManager::getTexturePath("fruit-bananas.png"));
                                           }
                                       });

        fruitwork::AnimatedSprite *animatedSprite = fruitwork::AnimatedSprite::getInstance(450, 600, 392 / 2, 348 / 2, ResourceManager::getTexturePath("pippi-{n}.png"), 500);

        fruitwork::Button *testButton = fruitwork::Button::getInstance(10, 842, 240, 48, "Back to index");
        testButton->registerCallback([](fruitwork::Button *src)
                                     {
                                         fruitwork::sys.setNextScene(fruitwork::TestSceneIndex::getInstance());
                                     });
        testButton->setColor({255, 255, 255, 128});
        testButton->setTextColor({0, 0, 0, 128});

        addComponent(title);

        addComponent(smallButton);
        addComponent(smallButton2);
        addComponent(mediumButton);
        addComponent(largeButton);
        addComponent(tallButton);

        addComponent(inputField);
        addComponent(passwordInputField);
        addComponent(numericInputField);

        addComponent(leftAnchoredLabel);
        addComponent(centerAnchoredLabel);
        addComponent(rightAnchoredLabel);

        addComponent(sprite);
        addComponent(responsiveSprite);
        addComponent(sprite2);
        addComponent(responsiveSprite2);

        addComponent(imageButton);
        addComponent(imageButton2);

        addComponent(animatedSprite);

        addComponent(testButton);

        return success;
    }

    bool TestScene::exit()
    {
        bool success = true;
        SDL_Log("Exiting TestScene...");

        for (auto &c: components)
            removeComponent(c, true);

        return success;
    }

    TestScene::TestScene()
    =
    default;

    TestScene *TestScene::getInstance()
    {
        return &instance;
    }

    TestScene TestScene::instance;

} // yuzu