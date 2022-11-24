#ifndef FRUITWORK_SPRITE_H
#define FRUITWORK_SPRITE_H

#include <string>
#include <SDL.h>
#include "Component.h"

namespace fruitwork
{

    class Sprite : public Component {

    public:
        static Sprite *getInstance(int x, int y, int w, int h, const std::string &texturePath);

        static Sprite *getInstance(int x, int y, int w, int h, SDL_Texture *texture);

        void draw() const override;

        void setColorMod(const SDL_Color &color) { this->colorMod = color; }

        void setFlip(SDL_RendererFlip flip) { this->flipType = flip; }

        ~Sprite() override;

    protected:
        Sprite(int x, int y, int w, int h, const std::string &texturePath);

        Sprite(int x, int y, int w, int h);

        SDL_Texture *spriteTexture;

        /**  If true, the texture will be destroyed when the sprite is destroyed. */
        bool isTextureOwner = true;
    private:
        SDL_Color colorMod = {255, 255, 255, 255};
        SDL_RendererFlip flipType = SDL_FLIP_NONE;

    };

} // fruitwork

#endif //FRUITWORK_SPRITE_H
