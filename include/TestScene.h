#ifndef FRUITWORK_TEST_SCENE_H
#define FRUITWORK_TEST_SCENE_H

#include "Scene.h"

namespace fruitwork
{

    class TestScene : public Scene {
    public:
        static TestScene *getInstance();

        bool enter() override;

        bool exit() override;


    private:
        static TestScene instance;

        TestScene();
    };

} // fruitwork

#endif //FRUITWORK_TEST_SCENE_H
