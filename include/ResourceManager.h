#ifndef FRUITWORK_RESOURCEMANAGER_H
#define FRUITWORK_RESOURCEMANAGER_H

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

#endif //FRUITWORK_RESOURCEMANAGER_H
