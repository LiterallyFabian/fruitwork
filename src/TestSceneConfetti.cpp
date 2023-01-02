#include "TestSceneConfetti.h"
#include "System.h"
#include "Button.h"
#include "Label.h"
#include "TestSceneIndex.h"
#include "ConfettiCannon.h"
#include "ResourceManager.h"

namespace fruitwork
{
    bool fruitwork::TestSceneConfetti::enter()
    {
        Label *titleText = fruitwork::Label::getInstance(0, 25, 1200, 900, "Visual tests::Confetti");
        titleText->setAlignment(fruitwork::Label::Alignment::CENTER);
        titleText->setFontSize(100);

        // test scene button
        Button *testButton = fruitwork::Button::getInstance(10, 842, 240, 48, "Back to index");
        testButton->registerCallback([](fruitwork::Button *src)
                                     {
                                         fruitwork::sys.setNextScene(fruitwork::TestSceneIndex::getInstance());
                                     });


        ConfettiCannon *confettiCannonCenter = ConfettiCannon::getInstance(1200 / 2, 900 / 2, 24, 24, ResourceManager::getTexturePath("star.png"));

        ConfettiCannon *confettiCannonRightCorner = ConfettiCannon::getInstance(1200, 900, 24, 24, ResourceManager::getTexturePath("star.png"));
        confettiCannonRightCorner->setColors({{255, 0,   0,   255},
                                              {0,   255, 0,   255},
                                              {0,   0,   255, 255}
                                             });

        ConfettiCannon *confettiCannonAnotherImage = ConfettiCannon::getInstance(1240 / 2, 900, 50, 50, ResourceManager::getTexturePath("jerafina.png"));
        confettiCannonAnotherImage->setColors({{255, 255, 255, 255}});

        Button *buttonCenter360 = fruitwork::Button::getInstance(20, 600, 240, 48, "Center, 360spr");
        buttonCenter360->registerCallback([confettiCannonCenter](fruitwork::Button *src)
                                          {
                                              confettiCannonCenter->fire(0, 360, 200, 1500);
                                          });

        Button *buttonRightTowardsCenter = fruitwork::Button::getInstance(20, 650, 240, 48, "Right corner, 45deg");
        buttonRightTowardsCenter->registerCallback([confettiCannonRightCorner](fruitwork::Button *src)
                                                   {
                                                       confettiCannonRightCorner->fire(225, 20, 100, 1000, 3000);
                                                   });

        Button *buttonAnotherImage = fruitwork::Button::getInstance(20, 700, 240, 48, "Another image");
        buttonAnotherImage->registerCallback([confettiCannonAnotherImage](fruitwork::Button *src)
                                             {
                                                 confettiCannonAnotherImage->fire(-90, 90, 100, 200);
                                             });

        addComponent(titleText);
        addComponent(testButton);

        addComponent(confettiCannonCenter);
        addComponent(confettiCannonRightCorner);
        addComponent(confettiCannonAnotherImage);

        addComponent(buttonCenter360);
        addComponent(buttonRightTowardsCenter);
        addComponent(buttonAnotherImage);

        return true;
    }

    bool TestSceneConfetti::exit()
    {
        bool success = true;
        SDL_Log("Exiting TestSceneConfetti...");

        for (auto &c: components)
            removeComponent(c, true);

        return success;
    }

    TestSceneConfetti TestSceneConfetti::instance;

} // fruitwork