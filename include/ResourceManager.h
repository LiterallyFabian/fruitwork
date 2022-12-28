#ifndef FRUITWORK_RESOURCE_MANAGER_H
#define FRUITWORK_RESOURCE_MANAGER_H

#include <string>

namespace fruitwork
{

    class ResourceManager {
    public:
        static std::string getTexturePath(const std::string& textureName);

        static std::string getFontPath(const std::string& fontName);

        static std::string getAudioPath(const std::string& clipName);
    };

} // fruitwork

#endif //FRUITWORK_RESOURCE_MANAGER_H
