#include "AnimatedSprite.h"
#include "System.h"
#include "Constants.h"
#include <sys/stat.h>
#include <SDL_image.h>

namespace fruitwork
{
    /**
    * @see https://stackoverflow.com/a/12774387
    */
    inline bool file_exists(const std::string &path)
    {
        struct stat buffer{};
        return (stat(path.c_str(), &buffer) == 0);
    }

    AnimatedSprite *AnimatedSprite::getInstance(int x, int y, int w, int h, const std::string &animationName, Uint32 animationSpeed)
    {
        return new AnimatedSprite(x, y, w, h, animationName, animationSpeed);
    }

    AnimatedSprite::AnimatedSprite(int x, int y, int w, int h, const std::string &animationName, Uint32 animationSpeed) :
            Sprite(x, y, w, h), animationName(animationName), animationSpeed(animationSpeed)
    {
        int i = 0;
        while (true)
        {
            std::string path = constants::gResPath + "images/" + animationName;  // NOLINT(performance-inefficient-string-concatenation)
            std::string frameNumber = std::to_string(i);
            path.replace(path.find("{n}"), 3, frameNumber);
            if (file_exists(path))
            {
                SDL_Surface *surface = IMG_Load(path.c_str());
                if (surface == nullptr)
                    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load animation image: %s", path.c_str());
                SDL_Texture *texture = SDL_CreateTextureFromSurface(sys.get_renderer(), surface);
                SDL_FreeSurface(surface);
                frames.push_back(texture);
                i++;
            }
            else
            {
                break;
            }
        }

        if (frames.empty())
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                         "Failed to load animation: %s. If nothing else is logged, the path might be incorrect or a start frame (N=0) might be missing.", animationName.c_str());

        frameCount = (int) frames.size();
    }

    void AnimatedSprite::update()
    {
        if (frameCount == 0)
            return;

        Uint32 ticks = SDL_GetTicks();

        if (ticks - lastFrame > animationSpeed)
        {
            frame = (frame + 1) % frameCount;
            lastFrame = ticks;
        }

        spriteTexture = frames[frame];
    }

    AnimatedSprite::~AnimatedSprite()
    {
        for (SDL_Texture *f: frames)
            SDL_DestroyTexture(f);
    }

} // fruitwork