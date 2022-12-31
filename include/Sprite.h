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

        void update(float elapsedTime) override;

        void setColorMod(const SDL_Color &color) { this->colorMod = color; }

        SDL_Color getColorMod() const { return colorMod; }

        void setAlphaMod(Uint8 alpha) { this->alphaMod = alpha; }

        Uint8 getAlphaMod() const { return alphaMod; }

        void setFlip(SDL_RendererFlip flip) { this->flipType = flip; }

        SDL_RendererFlip getFlip() const { return flipType; }

        void fadeTo(int duration, Uint8 alpha, int delay = 0);

        void fadeOut(int duration, int delay = 0);

        void fadeIn(int duration, int delay = 0);

        virtual void setTexture(const std::string &texturePath);

        virtual void setTexture(const std::string &texturePath, bool keepSurface);

        virtual void setTexture(SDL_Texture *texture);

        /**
         * Checks if the rect of the sprite is colliding with the rect of another sprite.
         * @param other The other sprite to check collision with.
         * @param threshold The threshold of collision. If the threshold is 5, then the sprites must be at least 5 pixels apart to be considered colliding.
         * @return true if the rects are colliding, false otherwise.
         */
        bool rectCollidesWith(const Sprite *other, int threshold = 0) const;

        /**
         * Checks if the rect of the sprite is colliding with the pixels of another sprite.
         * To use this you need to keep the surface when creating the sprite.
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
        bool isTextureOwner = true; // TODO replace with smart pointers?
        bool isSurfaceOwner = true;

    private:
        SDL_Color colorMod = {255, 255, 255, 255};
        Uint8 alphaMod = 255;
        SDL_RendererFlip flipType = SDL_FLIP_NONE;

        // fade stuff
        bool isFading = false;
        Uint8 fadeAlpha = 255; // target alpha
        int fadeDuration = 0;
        int fadeDelay = 0;
        Uint64 fadeStartTime = 0;
    };

} // fruitwork

#endif //FRUITWORK_SPRITE_H
