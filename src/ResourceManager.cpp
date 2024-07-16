#include "Constants.h"
#include "ResourceManager.h"
#include <sys/stat.h>
#include <string>
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

    /**
     * Get the relative path to a texture file.
     * @param textureName the name of the texture file, including the extension. it will be assumed to be in the images directory, but subdirectories can be specified (e.g. "subdir/texture.png")
     * @return the relative path to the texture file (e.g. "res/images/subdir/texture.png")
     */
    std::string ResourceManager::getTexturePath(const std::string &textureName)
    {
        std::string path = constants::gResPath + "images/" + textureName;

        if (textureName.find("{n}") == std::string::npos && !file_exists(path))
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to find image at path: %s", path.c_str());

        return path;
    }

    std::string ResourceManager::getFontPath(const std::string &fontName)
    {
        bool hasExtension = fontName.find(".ttf") != std::string::npos;

        std::string path = constants::gResPath + "fonts/" + fontName + (hasExtension ? "" : ".ttf");
        if (!file_exists(path))
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to find font at path: %s", fontName.c_str());

        return path;
    }

    std::string ResourceManager::getAudioPath(const std::string &clipName)
    {
        std::string path = constants::gResPath + "sounds/" + clipName;
        if (!file_exists(path))
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to find audio clip at path: %s", clipName.c_str());

        return path;
    }


} // fruitwork