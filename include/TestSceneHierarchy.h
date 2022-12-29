#ifndef FRUITWORK_TEST_SCENE_HIERARCHY_H
#define FRUITWORK_TEST_SCENE_HIERARCHY_H

#include "Scene.h"
#include "Sprite.h"

namespace fruitwork
{

    class TestSceneHierarchy : public Scene {
    public:
        static TestSceneHierarchy *getInstance() { return &instance; }

        bool enter() override;

        void update() override;

        bool exit() override;

    private:
        static TestSceneHierarchy instance;

        fruitwork::Sprite *parent = nullptr;
        fruitwork::Sprite *child = nullptr;
        bool attached = false;

        TestSceneHierarchy() = default;
    };

} // fruitwork

#endif //FRUITWORK_TEST_SCENE_HIERARCHY_H
