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
        // set the child's local position to its current position
//        child->localRect.x = child->rect.x - rect.x;
//        child->localRect.y = child->rect.y - rect.y;

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

        /*for (Component *child : children)
            child->update({rect.x, rect.y});*/
    }

    /*void Component::update(const SDL_Point &parentPos)
    {
        rect.x = parentPos.x + localRect.x;
        rect.y = parentPos.y + localRect.y;
    }*/

    void Component::setRect(const SDL_Rect &r)
    {
        rect = r;
        //localRect = r;

        /*if (parent != nullptr)
        {
            rect.x = parent->getRect().x + localRect.x;
            rect.y = parent->getRect().y + localRect.y;
        }*/
    }

    const SDL_Rect& Component::getAbsoluteRect() const
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

        int pivotOffsetX = static_cast<int>(pivot.x * thisRect.w);
        int pivotOffsetY = static_cast<int>(pivot.y * thisRect.h);

        switch (anchor)
        {
            case Anchor::TOP_LEFT:
                rect.x = parentRect.x + thisRect.x - pivotOffsetX;
                rect.y = parentRect.y + thisRect.y - pivotOffsetY;
                break;
            case Anchor::TOP_CENTER:
                rect.x = parentRect.x + thisRect.x + parentRect.w / 2 - thisRect.w / 2 - pivotOffsetX;
                rect.y = parentRect.y + thisRect.y - pivotOffsetY;
                break;
            case Anchor::TOP_RIGHT:
                rect.x = parentRect.x + thisRect.x + parentRect.w - thisRect.w - pivotOffsetX;
                rect.y = parentRect.y + thisRect.y - pivotOffsetY;
                break;
            case Anchor::CENTER_LEFT:
                rect.x = parentRect.x + thisRect.x - pivotOffsetX;
                rect.y = parentRect.y + thisRect.y + parentRect.h / 2 - thisRect.h / 2 - pivotOffsetY;
                break;
            case Anchor::CENTER:
                rect.x = parentRect.x + thisRect.x + parentRect.w / 2 - thisRect.w / 2 - pivotOffsetX;
                rect.y = parentRect.y + thisRect.y + parentRect.h / 2 - thisRect.h / 2 - pivotOffsetY;
                break;
            case Anchor::CENTER_RIGHT:
                rect.x = parentRect.x + thisRect.x + parentRect.w - thisRect.w - pivotOffsetX;
                rect.y = parentRect.y + thisRect.y + parentRect.h / 2 - thisRect.h / 2 - pivotOffsetY;
                break;
            case Anchor::BOTTOM_LEFT:
                rect.x = parentRect.x + thisRect.x - pivotOffsetX;
                rect.y = parentRect.y + thisRect.y + parentRect.h - thisRect.h - pivotOffsetY;
                break;
            case Anchor::BOTTOM_CENTER:
                rect.x = parentRect.x + thisRect.x + parentRect.w / 2 - thisRect.w / 2 - pivotOffsetX;
                rect.y = parentRect.y + thisRect.y + parentRect.h - thisRect.h - pivotOffsetY;
                break;
            case Anchor::BOTTOM_RIGHT:
                rect.x = parentRect.x + thisRect.x + parentRect.w - thisRect.w - pivotOffsetX;
                rect.y = parentRect.y + thisRect.y + parentRect.h - thisRect.h - pivotOffsetY;
                break;
        }

        absoluteRect = rect;
        return absoluteRect;
    }

    void Component::setPivot(Anchor anchorPivot)
    {
        switch (anchorPivot)
        {
            case Anchor::TOP_LEFT:
                pivot = {0.0f, 1.0f};
                break;
            case Anchor::TOP_CENTER:
                pivot = {0.5f, 1.0f};
                break;
            case Anchor::TOP_RIGHT:
                pivot = {1.0f, 1.0f};
                break;
            case Anchor::CENTER_LEFT:
                pivot = {0.0f, 0.5f};
                break;
            case Anchor::CENTER:
                pivot = {0.5f, 0.5f};
                break;
            case Anchor::CENTER_RIGHT:
                pivot = {1.0f, 0.5f};
                break;
            case Anchor::BOTTOM_LEFT:
                pivot = {0.0f, 0.0f};
                break;
            case Anchor::BOTTOM_CENTER:
                pivot = {0.5f, 0.0f};
                break;
            case Anchor::BOTTOM_RIGHT:
                pivot = {1.0f, 0.0f};
                break;
        }
    }

    void Component::setAnchorAndPivot(Anchor newAnchor)
    {
        this->anchor = newAnchor;
        setPivot(anchor);
    }

} // fruitwork