#include "Component.h"

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
        child->localRect.x = child->rect.x - rect.x;
        child->localRect.y = child->rect.y - rect.y;


        if (child->parent != nullptr)
        {
            child->parent->removeChild(child); // remove child from old parent
        }

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

    void Component::update(float elapsedTime) {
        if (body != nullptr)
        {
            body->update(elapsedTime);
            setRect(body->getRect());
        }

        for (Component *child: children)
            child->update({rect.x, rect.y});
    }

    void Component::update(const SDL_Point &parentPos) {
        rect.x = parentPos.x + localRect.x;
        rect.y = parentPos.y + localRect.y;
    }

    void Component::setRect(const SDL_Rect &r) {
        rect = r;
        localRect = r;

        if (parent != nullptr)
        {
            rect.x = parent->getRect().x + localRect.x;
            rect.y = parent->getRect().y + localRect.y;
        }
    }

} // fruitwork