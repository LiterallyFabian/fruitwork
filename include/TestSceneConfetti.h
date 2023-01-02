#ifndef FRUITWORK_TEST_SCENE_CONFETTI_H
#define FRUITWORK_TEST_SCENE_CONFETTI_H

#include "Scene.h"

namespace fruitwork
{
    class TestSceneConfetti : public Scene {
    public:
        static TestSceneConfetti *getInstance() { return &instance; }

        bool enter() override;

        bool exit() override;

    private:
        static TestSceneConfetti instance;

        TestSceneConfetti() = default;
    };

} // fruitwork

#endif //FRUITWORK_TEST_SCENE_CONFETTI_H
