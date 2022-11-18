#include "Constants.h"
#include "ResourceManager.h"
#include <sys/stat.h>
#include <string>
#include <iostream>
#include "SDL.h"

namespace fruitwork
{
    /**
     * Checks if a file exists at the given path.
     * @param path The path to check.
     * @return True if the file exists, false otherwise.
     * @see https://stackoverflow.com/a/12774387
     */
    inline bool file_exists(const std::string &path)
    {
        struct stat buffer{};
        return (stat(path.c_str(), &buffer) == 0);
    }

    std::string ResourceManager::getTexturePath(const std::string &textureName)
    {
        std::string path = constants::gResPath + "images/" + textureName;
        if (!file_exists(path))
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load image: %s", textureName.c_str());

        return path;
    }

    std::string ResourceManager::getFontPath(const std::string &fontName)
    {
        bool hasExtension = fontName.find(".ttf") != std::string::npos;

        std::string path = constants::gResPath + "fonts/" + fontName + (hasExtension ? "" : ".ttf");
        if (!file_exists(path))
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load font: %s", fontName.c_str());

        return path;
    }

    std::string ResourceManager::getAudioPath(const std::string &clipName)
    {
        std::string path = constants::gResPath + "sounds/" + clipName;
        if (!file_exists(path))
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load audio clip: %s", clipName.c_str());

        return path;
    }


} // fruitwork