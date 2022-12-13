#ifndef FRUITWORK_SPRITE_H
#define FRUITWORK_SPRITE_H

#include <string>
#include <SDL.h>
#include "Component.h"

namespace fruitwork
{

    class Sprite : public Component {

    public:
        /**
         * @brief Create a new Sprite instance.
         * @param keepSurface Whether to keep the surface after creating the texture.
         * The surface should be kept if you need collision detection on pixel level.
         * @return
         */
        static Sprite *getInstance(int x, int y, int w, int h, const std::string &texturePath, bool keepSurface = false);

        static Sprite *getInstance(int x, int y, int w, int h, SDL_Texture *texture);

        void draw() const override;

        void setColorMod(const SDL_Color &color) { this->colorMod = color; }

        void setAlphaMod(Uint8 alpha) { this->alphaMod = alpha; }

        void setFlip(SDL_RendererFlip flip) { this->flipType = flip; }

        virtual void setTexture(const std::string &texturePath);

        virtual void setTexture(SDL_Texture *texture);

        /**
         * Checks if the rect of the sprite is colliding with the rect of another sprite.
         * @param other The other sprite to check collision with.
         * @return true if the rects are colliding, false otherwise.
         */
        bool rectCollidesWith(const Sprite *other) const;

        /**
         * Checks if the rect of the sprite is colliding with the pixels of another sprite.
         * @param other The other sprite to check collision with.
         * @param alpha The alpha value to consider as transparent. Default is 10 (basically invisible).
         * @return true if the rects are colliding, false otherwise.
         */
        bool pixelCollidesWith(const Sprite *other, Uint8 alpha = 10) const;

        ~Sprite() override;

    protected:
        Sprite(int x, int y, int w, int h, const std::string &texturePath, bool keepSurface = false);

        Sprite(int x, int y, int w, int h, SDL_Texture *texture);

        SDL_Texture *spriteTexture = nullptr;
        SDL_Surface *surface = nullptr;

        /**  If true, the texture will be destroyed when the sprite is destroyed. */
        bool isTextureOwner = true;
        bool isSurfaceOwner = true;

    private:
        SDL_Color colorMod = {255, 255, 255, 255};
        Uint8 alphaMod = 255;
        SDL_RendererFlip flipType = SDL_FLIP_NONE;
    };

} // fruitwork

#endif //FRUITWORK_SPRITE_H
