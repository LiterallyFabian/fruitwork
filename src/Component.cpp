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
        SDL_Rect localRect = getRect();
        SDL_Rect parentAbsoluteRect; // if no component parent, we use the window size
        if (parent == nullptr)
        {
            SDL_Window *window = fruitwork::sys.getWindow();
            SDL_GetWindowSize(window, &parentAbsoluteRect.w, &parentAbsoluteRect.h);
            parentAbsoluteRect.x = 0;
            parentAbsoluteRect.y = 0;
        }
        else
        {
            parentAbsoluteRect = parent->getAbsoluteRect();
        }

        SDL_Rect newAbsoluteRect = localRect;

        switch (anchor)
        {
            case Anchor::LEGACY_TOP_LEFT:
                newAbsoluteRect.x = parentAbsoluteRect.x + localRect.x;
                newAbsoluteRect.y = parentAbsoluteRect.y + localRect.y;
                break;
            case Anchor::TOP_LEFT:
                newAbsoluteRect.x = parentAbsoluteRect.x + localRect.x;
                newAbsoluteRect.y = parentAbsoluteRect.y - localRect.y;
                break;
            case Anchor::TOP_CENTER:
                newAbsoluteRect.x = parentAbsoluteRect.x + localRect.x + parentAbsoluteRect.w / 2 - localRect.w / 2;
                newAbsoluteRect.y = parentAbsoluteRect.y - localRect.y;
                break;
            case Anchor::TOP_RIGHT:
                newAbsoluteRect.x = parentAbsoluteRect.x + localRect.x + parentAbsoluteRect.w - localRect.w;
                newAbsoluteRect.y = parentAbsoluteRect.y - localRect.y;
                break;
            case Anchor::CENTER_LEFT:
                newAbsoluteRect.x = parentAbsoluteRect.x + localRect.x;
                newAbsoluteRect.y = parentAbsoluteRect.y - localRect.y + parentAbsoluteRect.h / 2 - localRect.h / 2;
                break;
            case Anchor::CENTER:
                newAbsoluteRect.x = parentAbsoluteRect.x + localRect.x + parentAbsoluteRect.w / 2 - localRect.w / 2;
                newAbsoluteRect.y = parentAbsoluteRect.y - localRect.y + parentAbsoluteRect.h / 2 - localRect.h / 2;
                break;
            case Anchor::CENTER_RIGHT:
                newAbsoluteRect.x = parentAbsoluteRect.x + localRect.x + parentAbsoluteRect.w - localRect.w;
                newAbsoluteRect.y = parentAbsoluteRect.y - localRect.y + parentAbsoluteRect.h / 2 - localRect.h / 2;
                break;
            case Anchor::BOTTOM_LEFT:
                newAbsoluteRect.x = parentAbsoluteRect.x + localRect.x;
                newAbsoluteRect.y = parentAbsoluteRect.y - localRect.y + parentAbsoluteRect.h - localRect.h;
                break;
            case Anchor::BOTTOM_CENTER:
                newAbsoluteRect.x = parentAbsoluteRect.x + localRect.x + parentAbsoluteRect.w / 2 - localRect.w / 2;
                newAbsoluteRect.y = parentAbsoluteRect.y - localRect.y + parentAbsoluteRect.h - localRect.h;
                break;
            case Anchor::BOTTOM_RIGHT:
                newAbsoluteRect.x = parentAbsoluteRect.x + localRect.x + parentAbsoluteRect.w - localRect.w;
                newAbsoluteRect.y = parentAbsoluteRect.y - localRect.y + parentAbsoluteRect.h - localRect.h;
                break;

            case Anchor::TOP_STRETCH:
                newAbsoluteRect.x = parentAbsoluteRect.x + localRect.x;
                newAbsoluteRect.y = parentAbsoluteRect.y - localRect.y; // based on Unity implementation of stretch, might look weird
                newAbsoluteRect.w = parentAbsoluteRect.w - localRect.w - localRect.x;
                newAbsoluteRect.h = localRect.h;
                break;
            case Anchor::CENTER_STRETCH:
                newAbsoluteRect.x = parentAbsoluteRect.x + localRect.x;
                newAbsoluteRect.y = parentAbsoluteRect.y + parentAbsoluteRect.h / 2 - localRect.h / 2 - localRect.y;
                newAbsoluteRect.w = parentAbsoluteRect.w - localRect.x - localRect.w;
                newAbsoluteRect.h = localRect.h;
                break;
            case Anchor::BOTTOM_STRETCH:
                newAbsoluteRect.x = parentAbsoluteRect.x + localRect.x;
                newAbsoluteRect.y = parentAbsoluteRect.y + parentAbsoluteRect.h - localRect.h - localRect.y;
                newAbsoluteRect.w = parentAbsoluteRect.w - localRect.x - localRect.w;
                newAbsoluteRect.h = localRect.h;
                break;
            case Anchor::STRETCH:
                newAbsoluteRect.x = parentAbsoluteRect.x + localRect.x;
                newAbsoluteRect.y = parentAbsoluteRect.y + localRect.y;
                newAbsoluteRect.w = parentAbsoluteRect.w - localRect.w * 2;
                newAbsoluteRect.h = parentAbsoluteRect.h - localRect.h * 2;
                break;
            case Anchor::STRETCH_LEFT:
                newAbsoluteRect.x = parentAbsoluteRect.x + localRect.x;
                newAbsoluteRect.y = parentAbsoluteRect.y + localRect.y;
                newAbsoluteRect.w = localRect.w;
                newAbsoluteRect.h = parentAbsoluteRect.h - localRect.y - localRect.h;
                break;
            case Anchor::STRETCH_RIGHT:
                newAbsoluteRect.x = parentAbsoluteRect.x + parentAbsoluteRect.w - localRect.w + localRect.x;
                newAbsoluteRect.y = parentAbsoluteRect.y + localRect.y;
                newAbsoluteRect.w = localRect.w;
                newAbsoluteRect.h = parentAbsoluteRect.h - localRect.y - localRect.h;
                break;
            case Anchor::STRETCH_CENTER:
                newAbsoluteRect.x = parentAbsoluteRect.x + localRect.x + parentAbsoluteRect.w / 2 - localRect.w / 2;
                newAbsoluteRect.y = parentAbsoluteRect.y + localRect.y;
                newAbsoluteRect.w = localRect.w;
                newAbsoluteRect.h = parentAbsoluteRect.h - localRect.y - localRect.h;
                break;
        }

        absoluteRect = newAbsoluteRect;
        return absoluteRect;
    }

    SDL_Point Component::getPivot() const
    {
        SDL_FPoint normalizedPivot = {0.0f, 0.0f};
        switch (getAnchor())
        {
            case Anchor::TOP_LEFT:
            case Anchor::LEGACY_TOP_LEFT: // todo: verify this
                normalizedPivot = {0.0f, 1.0f};
                break;
            case Anchor::TOP_CENTER:
            case Anchor::TOP_STRETCH:
                normalizedPivot = {0.5f, 1.0f};
                break;
            case Anchor::TOP_RIGHT:
                normalizedPivot = {1.0f, 1.0f};
                break;
            case Anchor::CENTER_LEFT:
            case Anchor::STRETCH_LEFT:
                normalizedPivot = {0.0f, 0.5f};
                break;
            case Anchor::CENTER:
            case Anchor::CENTER_STRETCH:
            case Anchor::STRETCH_CENTER:
            case Anchor::STRETCH:
                normalizedPivot = {0.5f, 0.5f};
                break;
            case Anchor::CENTER_RIGHT:
            case Anchor::STRETCH_RIGHT:
                normalizedPivot = {1.0f, 0.5f};
                break;
            case Anchor::BOTTOM_LEFT:
                normalizedPivot = {0.0f, 0.0f};
                break;
            case Anchor::BOTTOM_CENTER:
            case Anchor::BOTTOM_STRETCH:
                normalizedPivot = {0.5f, 0.0f};
                break;
            case Anchor::BOTTOM_RIGHT:
                normalizedPivot = {1.0f, 0.0f};
                break;
        }

        SDL_Point pivot = {(int)(absoluteRect.w * normalizedPivot.x), (int)(absoluteRect.h * normalizedPivot.y)};
        return pivot;
    }

    double Component::getAbsoluteAngle() const
    {
        if (parent == nullptr)
            return angle;

        return angle + parent->getAbsoluteAngle();
    }

} // fruitwork