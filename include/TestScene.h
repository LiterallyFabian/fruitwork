#ifndef FRUITWORK_TESTSCENE_H
#define FRUITWORK_TESTSCENE_H

#include "Scene.h"

namespace fruitwork
{

    class TestScene : public Scene {
    public:
        static TestScene *get_instance();

        bool enter() override;

        bool exit() override;


    private:
        static TestScene instance;

        TestScene();
    };

} // fruitwork

#endif //FRUITWORK_TESTSCENE_H
