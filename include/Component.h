#ifndef FRUITWORK_COMPONENT_H
#define FRUITWORK_COMPONENT_H

#include <SDL.h>
#include <vector>
#include "PhysicsBody.h"

namespace fruitwork
{

    class Component
    {

    public:
        virtual ~Component();

        Component(const Component &) = delete; // no copy constructor

        const Component &operator=(const Component &) = delete; // no copy assignment

        /** Called when a mouse button is pressed. The mouse does not have to be over the component. */
        virtual void onMouseDown(const SDL_Event &) {};

        /** Called when a mouse button is released. The mouse does not have to be over the component. */
        virtual void onMouseUp(const SDL_Event &) {};

        /** Called when a key is pressed. */
        virtual void onKeyDown(const SDL_Event &) {};

        /** Called when a key is released. */
        virtual void onKeyUp(const SDL_Event &) {};

        /** Called when text input is received. This is not the same as key down. */
        virtual void onTextInput(const SDL_Event &) {};

        /** Called when text is being edited. This is commonly used in languages like Japanese where composing characters may require multiple keystrokes. */
        virtual void onTextEditing(const SDL_Event &) {};

        /**
         * Called once per frame, after the component has been updated.
         * @see fruitwork::Component::update
         */
        virtual void draw() const = 0;

        /** Update is called every frame. */
        virtual void update() {};

        /**
         * Update is called every frame.
         * @param elapsedTime The time in seconds since the last frame.
         */
        virtual void update(float elapsedTime);

        /**
         * Update the position of the component based on the parent position.
         * @param parentPos The position of the parent component.
         */
        virtual void update(const SDL_Point &parentPos);

        /**
         * Start is called when the component is added to a session.
         */
        virtual void start() {};

        const SDL_Rect &getRect() const { return rect; }

        const SDL_Rect &getLocalRect() const { return localRect; }

        /**
         * Sets the rect of the component. This will also update the local rect.
         */
        void setRect(const SDL_Rect &r);

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
