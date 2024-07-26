#include <sstream>
#include "Scene.h"
#include "DebugInfo.h"

namespace fruitwork
{
    DebugInfo::DebugInfo(int x, int y, int w, int h, Scene *s) : Component(x, y, w, h), scene(s)
    {
        debugLabel = Label::getInstance(x, y, w, h, "Debug Info");
        debugLabel->setColor({153, 255, 153, 255});

        background = Rectangle::getInstance(x, y, w, h, {0, 0, 0, 64});
    }

    DebugInfo *fruitwork::DebugInfo::getInstance(Scene *scene)
    {
        return new DebugInfo(10, 10, 800, 1200, scene);
    }

    void DebugInfo::update()
    {
        if (SDL_GetTicks64() - lastUpdateTimestamp < millisecondsBetweenUpdates)
            return;

        lastUpdateTimestamp = SDL_GetTicks64();

        cachedText.clear();
        cachedText.reserve(4096);

        const auto &components = scene->getComponents();
        for (const Component *comp : components)
            collectDebugInfo(cachedText, comp, 0);

        debugLabel->setText(cachedText);
    }

    void fruitwork::DebugInfo::draw() const
    {
        background->draw();
        debugLabel->draw();
    }

    void DebugInfo::collectDebugInfo(std::string &text, const Component *comp, int level) const
    {
        if (!comp)
            return;

        std::string indent(level * 4, ' ');
        text.append(indent);

        std::string anchor;
        switch (comp->getAnchor())
        {
            case Anchor::TOP_LEFT:
                anchor = "TOP_LEFT";
                break;
            case Anchor::TOP_CENTER:
                anchor = "TOP_CENTER";
                break;
            case Anchor::TOP_RIGHT:
                anchor = "TOP_RIGHT";
                break;
            case Anchor::CENTER_LEFT:
                anchor = "CENTER_LEFT";
                break;
            case Anchor::CENTER:
                anchor = "CENTER";
                break;
            case Anchor::CENTER_RIGHT:
                anchor = "CENTER_RIGHT";
                break;
            case Anchor::BOTTOM_LEFT:
                anchor = "BOTTOM_LEFT";
                break;
            case Anchor::BOTTOM_CENTER:
                anchor = "BOTTOM_CENTER";
                break;
            case Anchor::BOTTOM_RIGHT:
                anchor = "BOTTOM_RIGHT";
                break;
        }

        const std::string className = typeid(*comp).name();
        text.append(className)
            .append(" at (")
            .append(std::to_string(comp->getRect().x))
            .append(", ")
            .append(std::to_string(comp->getRect().y))
            .append(") W:")
            .append(std::to_string(comp->getRect().w))
            .append(", H:")
            .append(std::to_string(comp->getRect().h))
            .append(", Z: ")
            .append(std::to_string(comp->zIndex()))
            .append(", A: ")
            .append(anchor)
            .append("\n");

        for (const Component *child : comp->getChildren())
            collectDebugInfo(text, child, level + 1);
    }

} // fruitwork