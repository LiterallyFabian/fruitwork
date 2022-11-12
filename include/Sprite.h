#ifndef FRUITWORK_SPRITE_H
#define FRUITWORK_SPRITE_H

#include <string>
#include <SDL.h>
#include "Component.h"

namespace fruitwork
{

    class Sprite : public Component {

    public:
        static Sprite *getInstance(int x, int y, int w, int h, const std::string& textureName);

        void draw() const override;

        ~Sprite() override;

    protected:
        Sprite(int x, int y, int w, int h, const std::string& textureName);

    private:
        SDL_Texture *spriteTexture;
    };

} // fruitwork

#endif //FRUITWORK_SPRITE_H
