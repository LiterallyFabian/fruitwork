#include "ResourceManager.h"
#include "Constants.h"

namespace fruitwork
{
    std::string ResourceManager::getTexturePath(const std::string &textureName)
    {
        return constants::gResPath + "images/" + textureName;
    }

    std::string ResourceManager::getFontPath(const std::string &fontName)
    {
        return constants::gResPath + "fonts/" + fontName;
    }

    std::string ResourceManager::getAudioPath(const std::string &clipName)
    {
        return constants::gResPath + "audio/" + clipName;
    }

} // fruitwork