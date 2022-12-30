#ifndef FRUITWORK_TEST_SCENE_COLLISION_H
#define FRUITWORK_TEST_SCENE_COLLISION_H

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

        fruitwork::Sprite *jerafina = nullptr;
        fruitwork::Sprite *lynn = nullptr;
        fruitwork::Sprite *bananas = nullptr;
    };

} // fruitwork

#endif //FRUITWORK_TEST_SCENE_COLLISION_H
