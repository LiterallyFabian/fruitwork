#ifndef FRUITWORK_TESTSCENECOLLISION_H
#define FRUITWORK_TESTSCENECOLLISION_H

#include "Scene.h"
#include "Sprite.h"

namespace fruitwork
{
    class TestSceneCollision : public Scene {
    public:
        static TestSceneCollision *getInstance() { return &instance; }

        bool enter() override;

        void update() override;

        bool exit() override;

    private:
        static TestSceneCollision instance;

        TestSceneCollision() = default;

        fruitwork::Sprite *pippi = nullptr;
        fruitwork::Sprite *lynn = nullptr;
        fruitwork::Sprite *bananas = nullptr;
    };

} // fruitwork

#endif //FRUITWORK_TESTSCENECOLLISION_H
