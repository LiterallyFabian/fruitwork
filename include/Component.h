#ifndef FRUITWORK_COMPONENT_H
#define FRUITWORK_COMPONENT_H

#include <SDL.h>
#include <vector>
#include "PhysicsBody.h"

namespace fruitwork
{

    class Component {

    public:
        virtual ~Component();

        Component(const Component &) = delete; // no copy constructor

        const Component &operator=(const Component &) = delete; // no copy assignment

        virtual void onMouseDown(const SDL_Event &) {};

        virtual void onMouseUp(const SDL_Event &) {};

        virtual void onKeyDown(const SDL_Event &) {};

        virtual void onKeyUp(const SDL_Event &) {};

        virtual void onTextInput(const SDL_Event &) {};

        virtual void onTextEditing(const SDL_Event &) {};

        virtual void draw() const = 0;

        /**
         * Update is called every frame.
         */
        virtual void update() {};

        virtual void update(float elapsedTime)
        {
            if (body != nullptr)
            {
                body->update(elapsedTime);
                setRect(body->getRect());
            }

            for (Component *child: children)
                child->update({rect.x, rect.y});
        }

        virtual void update(const SDL_Point &parentPos)
        {
            rect.x = parentPos.x + localRect.x;
            rect.y = parentPos.y + localRect.y;
        }

        /**
         * Start is called when the component is added to a session.
         */
        virtual void start() {};

        const SDL_Rect &getRect() const { return rect; }

        const SDL_Rect &getLocalRect() const { return localRect; }

        /**
         * Sets the rect of the component. This will also update the local rect.
         */
        void setRect(const SDL_Rect &r)
        {
            rect = r;
            localRect = r;
        }

        int zIndex() const { return z; }

        /**
         * Set the z-index of the component. The z-index determines the order in which components are drawn and updated.
         * Changing the z-index after the component has been added to a session or scene has no effect.
         * If two components have the same z-index, the order in which they are drawn and updated is the order in which they were added.
         * @param zIndex The z-index of the component.
         */
        void setZIndex(int zIndex) { z = zIndex; }

        void addChild(Component *child);

        void removeChild(Component *child);

        std::vector<Component *> getChildren() const { return children; }

        int width() const { return rect.w; }

        int height() const { return rect.h; }

        void setPhysicsBody(PhysicsBody *body) { this->body = body; }

        PhysicsBody *getPhysicsBody() const { return body; }


    protected:
        Component(int x, int y, int w, int h);

    private:
        SDL_Rect rect;
        SDL_Rect localRect;
        int z = 0; // z-index

        std::vector<Component *> children = std::vector<Component *>();
        Component *parent = nullptr;

        PhysicsBody *body = nullptr;
    };

} // fruitwork

#endif //FRUITWORK_COMPONENT_H
