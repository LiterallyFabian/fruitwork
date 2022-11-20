#ifndef FRUITWORK_SPRITE_H
#define FRUITWORK_SPRITE_H

#include <string>
#include <SDL.h>
#include "Component.h"

namespace fruitwork
{

    class Sprite : public Component {

    public:
        static Sprite *getInstance(int x, int y, int w, int h, const std::string &textureName);

        void draw() const override;

        void setColorMod(const SDL_Color &color) { this->colorMod = color; }

        ~Sprite() override;

    protected:
        Sprite(int x, int y, int w, int h, const std::string &textureName);

        Sprite(int x, int y, int w, int h);

        SDL_Texture *spriteTexture;

    private:
        SDL_Color colorMod = {255, 255, 255, 255};
    };

} // fruitwork

#endif //FRUITWORK_SPRITE_H
