#ifndef FRUITWORK_DEBUGINFO_H
#define FRUITWORK_DEBUGINFO_H

#include "Component.h"
#include "Label.h"
#include "Scene.h"
#include "Rectangle.h"

namespace fruitwork
{

    class DebugInfo : public Component
    {

    public:
        static DebugInfo *getInstance(Scene *scene);

        void update() override;

        void draw() const override;

    protected:
        DebugInfo(int x, int y, int w, int h, Scene *s);

        void collectDebugInfo(std::string &text, const Component *comp, int level) const;

    private:
        Label *debugLabel = nullptr;
        Scene *scene = nullptr;
        const Uint64 millisecondsBetweenUpdates = 1000;
        Uint64 lastUpdateTimestamp = -millisecondsBetweenUpdates;

        std::string cachedText;

        fruitwork::Rectangle *background = nullptr;

    };

} // fruitwork

#endif //FRUITWORK_DEBUGINFO_H
