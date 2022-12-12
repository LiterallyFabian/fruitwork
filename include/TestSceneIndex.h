#ifndef FRUITWORK_TESTSCENEINDEX_H
#define FRUITWORK_TESTSCENEINDEX_H

#include "Scene.h"

namespace fruitwork
{
    class TestSceneIndex : public Scene {
    public:
        static TestSceneIndex *get_instance() { return &instance; }

        bool enter() override;

        bool exit() override;

    private:
        static TestSceneIndex instance;

        TestSceneIndex() = default;
    };

} // fruitwork

#endif //FRUITWORK_TESTSCENEINDEX_H
