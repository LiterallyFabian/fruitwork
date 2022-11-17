#ifndef FRUITWORK_EXITSCENE_H
#define FRUITWORK_EXITSCENE_H

#include "Scene.h"

namespace fruitwork
{

    class ExitScene : public Scene {

    public:
        static ExitScene *get_instance();

        bool enter() override;

        bool exit() override;

        void handleEvent(SDL_Event &e) override;

        void update() override;

        void draw() override;

    private:
        static ExitScene instance;

        ExitScene();
    };

} // fruitwork

#endif //FRUITWORK_EXITSCENE_H
