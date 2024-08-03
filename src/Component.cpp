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
        SDL_Rect parentAbsoluteRect = getParentAbsoluteRect();

        SDL_Rect newAbsoluteRect;

        SDL_Point sizeDelta = getSizeDelta();

        newAbsoluteRect.x = parentAbsoluteRect.x + static_cast<int>(parentAbsoluteRect.w * anchorMin.x) + localRect.x - static_cast<int>(sizeDelta.x * normalizedPivot.x);
        newAbsoluteRect.y = parentAbsoluteRect.y + parentAbsoluteRect.h - static_cast<int>(parentAbsoluteRect.h * anchorMin.y) - localRect.y - localRect.h + static_cast<int>(sizeDelta.y * normalizedPivot.y);
        newAbsoluteRect.w = sizeDelta.x;
        newAbsoluteRect.h = sizeDelta.y;

        if (anchorPreset == Anchor::LEGACY_TOP_LEFT)
        {
            newAbsoluteRect.x = parentAbsoluteRect.x + localRect.x;
            newAbsoluteRect.y = parentAbsoluteRect.y + localRect.y;
        }

        absoluteRect = newAbsoluteRect;
        return absoluteRect;
    }

    SDL_Rect Component::getParentAbsoluteRect() const
    {
        SDL_Rect parentAbsoluteRect; // if no component parent, we use the window size
        if (parent == nullptr)
        {
            SDL_Window *window = sys.getWindow();
            SDL_GetWindowSize(window, &parentAbsoluteRect.w, &parentAbsoluteRect.h);
            parentAbsoluteRect.x = 0;
            parentAbsoluteRect.y = 0;
        }
        else
        {
            parentAbsoluteRect = parent->getAbsoluteRect();
        }
        return parentAbsoluteRect;
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

    SDL_Point Component::getSizeDelta() const
    {
        SDL_Point sizeDelta;
        SDL_Point offsetMin = getOffsetMin();
        SDL_Point offsetMax = getOffsetMax();
        sizeDelta.x = offsetMax.x - offsetMin.x;
        sizeDelta.y = offsetMax.y - offsetMin.y;
        return sizeDelta;
    }

    SDL_Point Component::getOffsetMin() const
    {
        // See https://pixeleuphoria.com/blog/index.php/2020/05/10/unity-tip-recttransform/
        // ^ Great explanation of how to calculate offsetMin and offsetMax

        SDL_Point offset;
        SDL_Point anchoredPosition = getAnchoredPosition();
        offset.x = -normalizedPivot.x * rect.w + anchoredPosition.x;
        offset.y = -normalizedPivot.y * rect.h + anchoredPosition.y;
        return offset;
    }

    SDL_Point Component::getOffsetMax() const
    {
        SDL_Point offset;
        SDL_Point anchoredPosition = getAnchoredPosition();
        offset.x = (1.0 - normalizedPivot.x) * rect.w + anchoredPosition.x;
        offset.y = (1.0 - normalizedPivot.y) * rect.h + anchoredPosition.y;
        return offset;
    }

    SDL_Point Component::getAnchoredPosition() const
    {
        SDL_Point anchoredPosition;

        SDL_Rect parentRect = getParentAbsoluteRect();
        anchoredPosition.x = rect.x + anchorMin.x * parentRect.w + (anchorMax.x - anchorMin.x) * rect.w * normalizedPivot.x;
        anchoredPosition.y = rect.y + anchorMin.y * parentRect.h + (anchorMax.y - anchorMin.y) * rect.h * normalizedPivot.y;

        return anchoredPosition;
    }

} // fruitwork