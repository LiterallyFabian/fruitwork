#ifndef FRUITWORK_PHYSICS_BODY_H
#define FRUITWORK_PHYSICS_BODY_H

#include <SDL.h>

namespace fruitwork
{
    class PhysicsBody {
    public:
        static PhysicsBody *getInstance(SDL_Rect rect, float mass = 1.0f, float elasticity = 0.5f);

        virtual ~PhysicsBody();

        // disable copy constructor and assignment operator
        PhysicsBody(const PhysicsBody &) = delete;

        PhysicsBody &operator=(const PhysicsBody &) = delete;

        // update the physics body based on elapsed time and current velocity
        virtual void update(float elapsedTime);

        void addForce(float x, float y);

#pragma region getters/setters

        void setVelocity(float x, float y)
        {
            velocity.x = x;
            velocity.y = y;
        }

        void setVelocity(SDL_FPoint v) { this->velocity = v; }

        void setPosition(float x, float y)
        {
            position.x = x;
            position.y = y;
        }

        void setPosition(SDL_FPoint p) { this->position = p; }

        SDL_FPoint getVelocity() const { return velocity; }

        SDL_FPoint getPosition() const { return position; }

        void setMass(float m) { this->mass = m; }

        float getMass() const { return mass; }

        void setElasticity(float e) { this->elasticity = e; }

        float getElasticity() const { return elasticity; }

        void setGravity(float g) { this->gravityScale = g; }

        float getGravity() const { return gravityScale; }

        void setFriction(float f) { this->friction = f; }

        float getFriction() const { return friction; }

        void setScreenCollision(bool s) { this->screenCollision = s; }

        bool getScreenCollision() const { return screenCollision; }

        void setObjCollision(bool o) { this->objCollision = o; }

        bool getObjCollision() const { return objCollision; }

        // get the bounding box of the physics body
        const SDL_Rect &getRect() const { return rect; }

#pragma endregion

        // check if the physics body is colliding with another body
        bool isColliding(const PhysicsBody *) const;

        // resolve a collision with another body
        void resolveCollision(PhysicsBody *);

    protected:
        explicit PhysicsBody(SDL_Rect rect, float mass = 1.0f, float elasticity = 0.5f);

        // update the bounding box based on the current position
        void updateRect();


    private:
        SDL_Rect rect;
        SDL_FPoint velocity = {0.0f, 0.0f};
        SDL_FPoint position = {0.0f, 0.0f}; // to avoid rounding errors
        SDL_FPoint acceleration = {0.0f, 0.0f};
        float mass = 1.0f;
        float elasticity = 0.5f;
        float gravityScale = 0.0f;
        const float GRAVITY = 980;
        float friction = 0.05f;

        /** Whether or not the physics body should collide with the screen edges. */
        bool screenCollision = false;
        /** Whether or not the physics body should collide with other physics bodies. */
        bool objCollision = false;


    };
}

#endif // FRUITWORK_PHYSICS_BODY_H
