#include "Sprite.h"
#include "System.h"
#include "Constants.h"
#include "ResourceManager.h"
#include <SDL_image.h>

namespace fruitwork
{
    Sprite::Sprite(int x, int y, int w, int h, const std::string &textureName) : Component(x, y, w, h)
    {
        SDL_Surface *surface = IMG_Load(ResourceManager::getTexturePath(textureName).c_str());

        if (surface == nullptr)
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load image: %s", textureName.c_str());

        spriteTexture = SDL_CreateTextureFromSurface(sys.get_renderer(), surface);
        SDL_FreeSurface(surface);
    }

    Sprite::Sprite(int x, int y, int w, int h) : Component(x, y, w, h), spriteTexture(nullptr) {}

    Sprite *Sprite::getInstance(int x, int y, int w, int h, const std::string &textureName)
    {
        return new Sprite(x, y, w, h, textureName);
    }

    void Sprite::draw() const
    {
        if (spriteTexture != nullptr)
            SDL_RenderCopy(sys.get_renderer(), spriteTexture, nullptr, &get_rect());
    }

    Sprite::~Sprite()
    {
        SDL_DestroyTexture(spriteTexture);
    }


} // fruitwork