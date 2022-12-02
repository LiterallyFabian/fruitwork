#ifndef FRUITWORK_CONSTANTS_H
#define FRUITWORK_CONSTANTS_H

#include <string>

namespace constants
{
    const std::string gResPath = "../../resources/";
    const int gFps = 170;
    const int gScreenWidth = 1200;
    const int gScreenHeight = 900;

    const std::string gDefaultFontPath = gResPath + "fonts/Kepler 296.ttf";

    const double speedMod = 170.0 / gFps; // the game is designed to run at 170 fps, so we need to scale the speed accordingly
} // fruitwork

#endif //FRUITWORK_CONSTANTS_H
