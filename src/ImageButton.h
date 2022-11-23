#ifndef FRUITWORK_IMAGEBUTTON_H
#define FRUITWORK_IMAGEBUTTON_H

#include "Button.h"
#include "Sprite.h"

namespace fruitwork
{

    class ImageButton : public Button {
    public:
        static ImageButton *getInstance(int x, int y, int w, int h, SDL_Texture *texture);

        static ImageButton *getInstance(int x, int y, int w, int h, const std::string &texturePath);

        void draw() const override;

        ~ImageButton() override;

    protected:
        ImageButton(int x, int y, int w, int h, SDL_Texture *texture);

        ImageButton(int x, int y, int w, int h, const std::string &texturePath);

    private:
        SDL_Texture *texture;
        bool isSpriteOwner = true;
    };

} // fruitwork

#endif //FRUITWORK_IMAGEBUTTON_H
