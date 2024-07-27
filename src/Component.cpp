#include "Component.h"
#include "System.h"

namespace fruitwork
{

    Component::Component(int x, int y, int w, int h) : rect{x, y, w, h} {}

    Component::~Component()
    {
        children = std::vector<fruitwork::Component *>(); // idk why this is needed but it is

        delete body;
    }

    void Component::addChild(Component *child)
    {
        // remove child from old parent
        if (child->parent != nullptr)
            child->parent->removeChild(child);

        // add child to this component
        children.push_back(child);
        child->parent = this;
    }

    void Component::removeChild(Component *child)
    {
        for (auto it = children.begin(); it != children.end(); ++it)
        {
            if (*it == child)
            {
                children.erase(it);
                child->parent = nullptr;

                return;
            }
        }
    }

    void Component::update(float elapsedTime)
    {
        if (body != nullptr)
        {
            body->update(elapsedTime);
            setRect(body->getRect());
        }
    }

    const SDL_Rect &Component::getAbsoluteRect() const
    {
        SDL_Rect thisRect = getRect();
        SDL_Rect parentRect; // if no component parent, we use the window size
        if (parent == nullptr)
        {
            SDL_Window *window = fruitwork::sys.getWindow();
            SDL_GetWindowSize(window, &parentRect.w, &parentRect.h);
            parentRect.x = 0;
            parentRect.y = 0;
        }
        else
        {
            parentRect = parent->getAbsoluteRect();
        }

        SDL_Rect rect = thisRect;

        switch (anchor)
        {
            case Anchor::LEGACY_TOP_LEFT:
                rect.x = parentRect.x + thisRect.x;
                rect.y = parentRect.y + thisRect.y;
                break;
            case Anchor::TOP_LEFT:
                rect.x = parentRect.x + thisRect.x;
                rect.y = parentRect.y - thisRect.y;
                break;
            case Anchor::TOP_CENTER:
                rect.x = parentRect.x + thisRect.x + parentRect.w / 2 - thisRect.w / 2;
                rect.y = parentRect.y - thisRect.y;
                break;
            case Anchor::TOP_RIGHT:
                rect.x = parentRect.x + thisRect.x + parentRect.w - thisRect.w;
                rect.y = parentRect.y - thisRect.y;
                break;
            case Anchor::CENTER_LEFT:
                rect.x = parentRect.x + thisRect.x;
                rect.y = parentRect.y - thisRect.y + parentRect.h / 2 - thisRect.h / 2;
                break;
            case Anchor::CENTER:
                rect.x = parentRect.x + thisRect.x + parentRect.w / 2 - thisRect.w / 2;
                rect.y = parentRect.y - thisRect.y + parentRect.h / 2 - thisRect.h / 2;
                break;
            case Anchor::CENTER_RIGHT:
                rect.x = parentRect.x + thisRect.x + parentRect.w - thisRect.w;
                rect.y = parentRect.y - thisRect.y + parentRect.h / 2 - thisRect.h / 2;
                break;
            case Anchor::BOTTOM_LEFT:
                rect.x = parentRect.x + thisRect.x;
                rect.y = parentRect.y - thisRect.y + parentRect.h - thisRect.h;
                break;
            case Anchor::BOTTOM_CENTER:
                rect.x = parentRect.x + thisRect.x + parentRect.w / 2 - thisRect.w / 2;
                rect.y = parentRect.y - thisRect.y + parentRect.h - thisRect.h;
                break;
            case Anchor::BOTTOM_RIGHT:
                rect.x = parentRect.x + thisRect.x + parentRect.w - thisRect.w;
                rect.y = parentRect.y - thisRect.y + parentRect.h - thisRect.h;
                break;

            case Anchor::TOP_STRETCH:
                rect.x = parentRect.x + thisRect.x;
                rect.y = parentRect.y - thisRect.y; // based on Unity implementation of stretch, might look weird
                rect.w = parentRect.w - thisRect.w * 2;
                rect.h = thisRect.h;
                break;
            case Anchor::CENTER_STRETCH:
                rect.x = parentRect.x + thisRect.x;
                rect.y = parentRect.y + parentRect.h / 2 - thisRect.h / 2 - thisRect.y;
                rect.w = parentRect.w - thisRect.x * 2;
                rect.h = thisRect.h;
                break;
            case Anchor::BOTTOM_STRETCH:
                rect.x = parentRect.x + thisRect.x;
                rect.y = parentRect.y + parentRect.h - thisRect.h - thisRect.y;
                rect.w = parentRect.w - thisRect.x - thisRect.w;
                rect.h = thisRect.h;
                break;
            case Anchor::STRETCH:
                rect.x = parentRect.x + thisRect.x;
                rect.y = parentRect.y + thisRect.y;
                rect.w = parentRect.w - thisRect.w * 2;
                rect.h = parentRect.h - thisRect.h * 2;
                break;
            case Anchor::STRETCH_LEFT:
                rect.x = parentRect.x + thisRect.x;
                rect.y = parentRect.y + thisRect.y;
                rect.w = thisRect.w;
                rect.h = parentRect.h - thisRect.y * 2;
                break;
            case Anchor::STRETCH_RIGHT:
                rect.x = parentRect.x + parentRect.w - thisRect.w + thisRect.x;
                rect.y = parentRect.y + thisRect.y;
                rect.w = thisRect.w;
                rect.h = parentRect.h - thisRect.y * 2;
                break;
            case Anchor::STRETCH_CENTER:
                rect.x = parentRect.x + thisRect.x + parentRect.w / 2 - thisRect.w / 2;
                rect.y = parentRect.y + thisRect.y;
                rect.w = thisRect.w;
                rect.h = parentRect.h - thisRect.y * 2;
                break;
        }

        absoluteRect = rect;
        return absoluteRect;
    }

} // fruitwork