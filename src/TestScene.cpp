#include <iostream>
#include "TestScene.h"
#include "Label.h"
#include "Button.h"
#include "InputField.h"
#include "Sprite.h"
#include "ResponsiveSprite.h"

namespace fruitwork
{
    fruitwork::Label *title = fruitwork::Label::getInstance(0, 25, 1200, 900, "fruitwork::Visual tests");

    bool TestScene::enter()
    {
        bool success = true;
        std::cout << "TestScene::enter()" << std::endl;

        title->setAlignment(fruitwork::Label::Alignment::CENTER);
        title->setFontSize(100);
        title->setFont("Kepler 296.ttf");

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
        centerAnchoredLabel->setFont("Kepler 296.ttf");

        Label *rightAnchoredLabel = Label::getInstance(0, 850, 1200, 900, "Right anchored tiny label");
        rightAnchoredLabel->setAlignment(Label::Alignment::RIGHT);
        rightAnchoredLabel->setFontSize(12);

        // sprites that are too wide
        Sprite *sprite = Sprite::getInstance(650, 500, 256, 128, "jerafina.png");
        Sprite *responsiveSprite = ResponsiveSprite::getInstance(650, 650, 256, 128, "jerafina.png");

        // sprites that are too tall
        Sprite *sprite2 = Sprite::getInstance(950, 500, 128, 256, "jerafina.png");
        Sprite *responsiveSprite2 = ResponsiveSprite::getInstance(800, 650, 128, 256, "jerafina.png");

        add_component(title);

        add_component(smallButton);
        add_component(smallButton2);
        add_component(mediumButton);
        add_component(largeButton);
        add_component(tallButton);

        add_component(inputField);
        add_component(passwordInputField);
        add_component(numericInputField);

        add_component(leftAnchoredLabel);
        add_component(centerAnchoredLabel);
        add_component(rightAnchoredLabel);

        add_component(sprite);
        add_component(responsiveSprite);
        add_component(sprite2);
        add_component(responsiveSprite2);

        return success;
    }

    bool TestScene::exit()
    {
        bool success = true;
        std::cout << "Exiting TestScene" << std::endl;

        for (auto &c: components)
        {
            delete c;
        }

        return success;
    }

    TestScene::TestScene()
    =
    default;

    TestScene *TestScene::get_instance()
    {
        return &instance;
    }

    TestScene TestScene::instance;

} // yuzu