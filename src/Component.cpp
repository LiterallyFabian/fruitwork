#include <stdexcept>
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

        SDL_Rect newAbsoluteRect;

        newAbsoluteRect.x = parentAbsoluteRect.x + static_cast<int>(parentAbsoluteRect.w * anchorMin.x) + localRect.x;
        newAbsoluteRect.y = parentAbsoluteRect.y + static_cast<int>(parentAbsoluteRect.h * (1 - anchorMin.y)) - localRect.y;


        newAbsoluteRect.w = static_cast<int>(parentAbsoluteRect.w * (anchorMax.x - anchorMin.x)) + localRect.w;
        newAbsoluteRect.h = static_cast<int>(parentAbsoluteRect.h * (anchorMax.y - anchorMin.y)) + localRect.h;

        if (anchorPreset == Anchor::LEGACY_TOP_LEFT)
        {
            newAbsoluteRect.x = parentAbsoluteRect.x + localRect.x;
            newAbsoluteRect.y = parentAbsoluteRect.y + localRect.y;
        }

        absoluteRect = newAbsoluteRect;
        return absoluteRect;
    }

    SDL_Point Component::getPixelPivot() const
    {
        SDL_Point pivot = {(int)(absoluteRect.w * normalizedPivot.x), (int)(absoluteRect.h * normalizedPivot.y)};
        return pivot;
    }

    double Component::getAbsoluteAngle() const
    {
        if (parent == nullptr)
            return angle;

        return angle + parent->getAbsoluteAngle();
    }

    void Component::setAnchor(SDL_FPoint newAnchorMin, SDL_FPoint newAnchorMax)
    {
        anchorMin = newAnchorMin;
        anchorMax = newAnchorMax;
        anchorPreset = Anchor::CUSTOM;
    }

    void Component::setAnchorAndPivot(Anchor newAnchor)
    {
        setAnchor(newAnchor);
        setPivot(newAnchor);
    }

    void Component::setAnchor(Anchor newAnchor)
    {
        anchorPreset = newAnchor;

        switch (newAnchor)
        {
            case Anchor::TOP_LEFT:
            case Anchor::LEGACY_TOP_LEFT: // todo: verify legacy case
                anchorMin = {0.0f, 1.0f};
                anchorMax = {0.0f, 1.0f};
                return;
            case Anchor::TOP_CENTER:
                anchorMin = {0.5f, 1.0f};
                anchorMax = {0.5f, 1.0f};
                return;
            case Anchor::TOP_RIGHT:
                anchorMin = {1.0f, 1.0f};
                anchorMax = {1.0f, 1.0f};
                return;
            case Anchor::CENTER_LEFT:
                anchorMin = {0.0f, 0.5f};
                anchorMax = {0.0f, 0.5f};
                return;
            case Anchor::CENTER:
                anchorMin = {0.5f, 0.5f};
                anchorMax = {0.5f, 0.5f};
                return;
            case Anchor::CENTER_RIGHT:
                anchorMin = {1.0f, 0.5f};
                anchorMax = {1.0f, 0.5f};
                return;
            case Anchor::BOTTOM_LEFT:
                anchorMin = {0.0f, 0.0f};
                anchorMax = {0.0f, 0.0f};
                return;
            case Anchor::BOTTOM_CENTER:
                anchorMin = {0.5f, 0.0f};
                anchorMax = {0.5f, 0.0f};
                return;
            case Anchor::BOTTOM_RIGHT:
                anchorMin = {1.0f, 0.0f};
                anchorMax = {1.0f, 0.0f};
                return;
            case Anchor::TOP_STRETCH:
                anchorMin = {0.0f, 1.0f};
                anchorMax = {1.0f, 1.0f};
                return;
            case Anchor::CENTER_STRETCH:
                anchorMin = {0.0f, 0.5f};
                anchorMax = {1.0f, 0.5f};
                return;
            case Anchor::BOTTOM_STRETCH:
                anchorMin = {0.0f, 0.0f};
                anchorMax = {1.0f, 0.0f};
                return;
            case Anchor::STRETCH:
                anchorMin = {0.0f, 0.0f};
                anchorMax = {1.0f, 1.0f};
                return;
            case Anchor::STRETCH_LEFT:
                anchorMin = {0.0f, 0.0f};
                anchorMax = {0.0f, 1.0f};
                return;
            case Anchor::STRETCH_RIGHT:
                anchorMin = {1.0f, 0.0f};
                anchorMax = {1.0f, 1.0f};
                return;
            case Anchor::STRETCH_CENTER:
                anchorMin = {0.5f, 0.0f};
                anchorMax = {0.5f, 1.0f};
                return;
            case Anchor::CUSTOM:
                throw std::invalid_argument("Cannot set anchor to CUSTOM. Use setAnchor(SDL_FPoint, SDL_FPoint) instead.");
        }
    }

    void Component::setPivot(Anchor newAnchor)
    {
        switch (newAnchor)
        {
            case Anchor::TOP_LEFT:
            case Anchor::LEGACY_TOP_LEFT: // todo: verify legacy case
                normalizedPivot = {0.0f, 1.0f};
                return;
            case Anchor::TOP_CENTER:
                normalizedPivot = {0.5f, 1.0f};
                return;
            case Anchor::TOP_RIGHT:
                normalizedPivot = {1.0f, 1.0f};
                return;
            case Anchor::CENTER_LEFT:
                normalizedPivot = {0.0f, 0.5f};
                return;
            case Anchor::CENTER:
                normalizedPivot = {0.5f, 0.5f};
                return;
            case Anchor::CENTER_RIGHT:
                normalizedPivot = {1.0f, 0.5f};
                return;
            case Anchor::BOTTOM_LEFT:
                normalizedPivot = {0.0f, 0.0f};
                return;
            case Anchor::BOTTOM_CENTER:
                normalizedPivot = {0.5f, 0.0f};
                return;
            case Anchor::BOTTOM_RIGHT:
                normalizedPivot = {1.0f, 0.0f};
                return;
            case Anchor::TOP_STRETCH:
                normalizedPivot = {0.5f, 1.0f};
                return;
            case Anchor::CENTER_STRETCH:
                normalizedPivot = {0.5f, 0.5f};
                return;
            case Anchor::BOTTOM_STRETCH:
                normalizedPivot = {0.5f, 0.0f};
                return;
            case Anchor::STRETCH:
                normalizedPivot = {0.5f, 0.5f};
                return;
            case Anchor::STRETCH_LEFT:
                normalizedPivot = {0.0f, 0.5f};
                return;
            case Anchor::STRETCH_RIGHT:
                normalizedPivot = {1.0f, 0.5f};
                return;
            case Anchor::STRETCH_CENTER:
                normalizedPivot = {0.5f, 0.5f};
                return;
            case Anchor::CUSTOM:
                throw std::invalid_argument("Cannot set pivot to CUSTOM. Use setPivot(SDL_FPoint) instead.");
        }
    }

} // fruitwork