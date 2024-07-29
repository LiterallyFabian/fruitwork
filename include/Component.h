#ifndef FRUITWORK_COMPONENT_H
#define FRUITWORK_COMPONENT_H

#include <SDL.h>
#include <vector>
#include "PhysicsBody.h"

namespace fruitwork
{
    enum class Anchor
    {
        /**
         * Legacy top left will treat Y as the top of the screen, with positive Y going down.
         * All the other anchors, including custom will have a positive Y going up.
         * Using it should be avoided, but is kept for backwards compatibility.
         */
        LEGACY_TOP_LEFT,
        TOP_LEFT,
        TOP_CENTER,
        TOP_RIGHT,
        CENTER_LEFT,
        CENTER,
        CENTER_RIGHT,
        BOTTOM_LEFT,
        BOTTOM_CENTER,
        BOTTOM_RIGHT,
        TOP_STRETCH,
        CENTER_STRETCH,
        BOTTOM_STRETCH,
        /* STRETCH will stretch both horizontally and vertically.*/
        STRETCH,
        STRETCH_LEFT,
        STRETCH_RIGHT,
        STRETCH_CENTER,
        /* CUSTOM is when the anchorPreset values are set manually. */
        CUSTOM
    };

    /**
     * A component is a drawable object that can be added to a session or scene.
     * It also contains position, size and anchorPreset information.
     */
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
         * Start is called when the component is added to a session.
         */
        virtual void start() {};

        /**
         * @return The rect the component is drawn in. This value differs from its absolute rect, which is a
         * combination of the parent's rect and the component's local rect, including anchorPreset.
         */
        const SDL_Rect &getRect() const { return rect; }

        /**
         * @return A calculated, absolute rect based on the parent's rect, the component's local rect and anchorPreset.
         * This is the rect components should be drawn in.
         */
        const SDL_Rect &getAbsoluteRect() const;

        /**
         * Sets the rect of the component. This will also update the local rect.
         */
        void setRect(const SDL_Rect &r) { rect = r; }

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

        Component *getParent() const { return parent; }

        std::vector<Component *> getChildren() const { return children; }

        int width() const { return rect.w; }

        int height() const { return rect.h; }

        void setPhysicsBody(PhysicsBody *newBody) { this->body = newBody; }

        PhysicsBody *getPhysicsBody() const { return body; }

        /* Sets anchor values based on a preset */
        void setAnchor(Anchor newAnchor);

        /* Set anchor values to custom values. This will also set the preset to CUSTOM. */
        void setAnchor(SDL_FPoint newAnchorMin, SDL_FPoint newAnchorMax);

        /* Sets anchor and pivot values based on a preset */
        void setAnchorAndPivot(Anchor newAnchor);

        Anchor getAnchorPreset() const { return anchorPreset; }

        SDL_FPoint getAnchorMin() const { return anchorMin; }

        SDL_FPoint getAnchorMax() const { return anchorMax; }

        void setFlip(SDL_RendererFlip flip) { this->flipType = flip; }

        SDL_RendererFlip getFlip() const { return flipType; }

        void setAngle(double newAngle) { this->angle = newAngle; }

        double getAngle() const { return angle; }

        /** @return The absolute angle this component should be drawn at, relative to the parent. */
        double getAbsoluteAngle() const;

        SDL_FPoint getNormalizedPivot() const { return normalizedPivot; }

        SDL_Point getPixelPivot() const;

        /* Sets pivot values based on a preset */
        void setPivot(Anchor anchorPreset);

        void setPivot(SDL_FPoint newPivot) { this->normalizedPivot = newPivot; }

    protected:
        Component(int x, int y, int w, int h);

    private:
        SDL_Rect rect;
        mutable SDL_Rect absoluteRect;

        int z = 0; // z-index

        std::vector<Component *> children = std::vector<Component *>();
        Component *parent = nullptr;

        PhysicsBody *body = nullptr;

        Anchor anchorPreset = Anchor::LEGACY_TOP_LEFT;

        /** The normalized point in the parent rect that the lower left corner of the component is anchored to. */
        SDL_FPoint anchorMin = {0.0f, 1.0f};
        /** The normalized point in the parent rect that the upper right corner of the component is anchored to. */
        SDL_FPoint anchorMax = {0.0f, 1.0f};
        /**
         * The point point specified in normalized values between 0 and 1.
         * The point point is the origin of this rect around which the component rotates.
         * @see <a href="https://docs.unity3d.com/ScriptReference/RectTransform.html">RectTransform</a>
         */
        SDL_FPoint normalizedPivot = {0.0f, 1.0f};

        SDL_RendererFlip flipType = SDL_FLIP_NONE;
        double angle = 0;
    };

} // fruitwork

#endif //FRUITWORK_COMPONENT_H
