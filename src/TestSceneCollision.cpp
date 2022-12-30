#include "TestSceneCollision.h"
#include "System.h"
#include "Button.h"
#include "Label.h"
#include "TestSceneIndex.h"
#include "ResourceManager.h"
#include "Sprite.h"

namespace fruitwork
{
    bool fruitwork::TestSceneCollision::enter()
    {
        fruitwork::Label *titleText = fruitwork::Label::getInstance(0, 25, 1200, 900, "Visual tests::Collision");
        titleText->setAlignment(fruitwork::Label::Alignment::CENTER);
        titleText->setFontSize(100);

        // test scene button
        fruitwork::Button *testButton = fruitwork::Button::getInstance(10, 842, 240, 48, "Back to index");
        testButton->registerCallback([](fruitwork::Button *src)
                                     {
                                         fruitwork::sys.setNextScene(fruitwork::TestSceneIndex::getInstance());
                                     });
        testButton->setColor({255, 255, 255, 128});
        testButton->setTextColor({0, 0, 0, 128});

        jerafina = fruitwork::Sprite::getInstance(20, 200, 348, 348, fruitwork::ResourceManager::getTexturePath("jerafina.png"), true);
        lynn = fruitwork::Sprite::getInstance(600, 200, 610, 648, fruitwork::ResourceManager::getTexturePath("fruit-catcher-kiai.png"), true);
        bananas = fruitwork::Sprite::getInstance(0, 0, 128, 128, fruitwork::ResourceManager::getTexturePath("fruit-bananas.png"), true);

        addComponent(jerafina);
        addComponent(lynn);
        addComponent(bananas);
        addComponent(titleText);
        addComponent(testButton);

        return true;
    }

    void TestSceneCollision::update()
    {
        Scene::update();
        Uint8 collisionType = 0; // 0=none, 1=rect, 2=pixel

        // set banana position to the mouse position
        int x, y;
        SDL_GetMouseState(&x, &y);

        bananas->setRect({x - 64, y - 64, 128, 128});

        // check collision
        if (jerafina->rectCollidesWith(bananas, 50))
        {
            SDL_Log("Jerafina collides with bananas on RECT level, threshold 50");
            collisionType = 1;
        }
        else if (jerafina->pixelCollidesWith(bananas))
        {
            SDL_Log("Jerafina collides with bananas on PIXEL level");
            collisionType = 2;
        }

        if (lynn->pixelCollidesWith(bananas))
        {
            SDL_Log("Character collides with bananas on PIXEL level");
            collisionType = 2;

        }
        else if (lynn->rectCollidesWith(bananas))
        {
            SDL_Log("Character collides with bananas on RECT level");
            collisionType = 1;
        }

        // set color by collision type
        switch (collisionType)
        {
            case 1:
                bananas->setColorMod({255, 255, 0, 255});
                break;
            case 2:
                bananas->setColorMod({255, 0, 0, 255});
                break;
            default:
                bananas->setColorMod({255, 255, 255, 255});
                break;
        }
    }

    bool TestSceneCollision::exit()
    {
        bool success = true;
        SDL_Log("Exiting TestSceneIndex...");

        for (auto &c: components)
            removeComponent(c, true);

        return success;
    }

    TestSceneCollision TestSceneCollision::instance;

} // fruitwork