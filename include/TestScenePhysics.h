#ifndef FRUITWORK_TEST_SCENE_PHYSICS_H
#define FRUITWORK_TEST_SCENE_PHYSICS_H

#include "Scene.h"
#include "Label.h"
#include "Sprite.h"

namespace fruitwork
{

    class TestScenePhysics : public Scene {
    public:
        static TestScenePhysics *getInstance() { return &instance; }

        bool enter() override;

        void update() override;

        bool exit() override;

    private:
        static TestScenePhysics instance;

        TestScenePhysics() = default;

        fruitwork::Label *spriteMeta = nullptr;
        fruitwork::Sprite *sprite = nullptr;
    };

} // fruitwork

#endif //FRUITWORK_TEST_SCENE_PHYSICS_H
