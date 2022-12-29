#include "PhysicsBody.h"
#include "Constants.h"

namespace fruitwork
{

    PhysicsBody::PhysicsBody(SDL_Rect rect, float mass, float elasticity)
            : rect(rect), mass(mass), elasticity(elasticity)
    {
        position.x = rect.x * 1.0f;
        position.y = rect.y * 1.0f;
    }

    PhysicsBody::~PhysicsBody() = default;

    void PhysicsBody::update(float elapsedTime)
    {
        // apply friction and gravity, with mass taken into account
        acceleration.x = -velocity.x * (1 - friction) / mass;
        acceleration.y = -velocity.y * (1 - friction) / mass + gravityScale * GRAVITY;

        // update velocity based on acceleration
        float prevVelocityX = velocity.x;
        float prevVelocityY = velocity.y;
        velocity.x += acceleration.x * elapsedTime;
        velocity.y += acceleration.y * elapsedTime;

        // calculate a weighted average of the previous and current velocities
        velocity.x = prevVelocityX * 0.9f + velocity.x * 0.1f;
        velocity.y = prevVelocityY * 0.9f + velocity.y * 0.1f;

        // update position based on velocity
        position.x += velocity.x * elapsedTime;
        position.y += velocity.y * elapsedTime;

        if (screenCollision)
        {
            // check for collision with screen edges
            if (position.x < 0)
            {
                position.x = 0;
                velocity.x *= -elasticity;
            }
            else if (position.x + rect.w > constants::gScreenWidth)
            {
                position.x = constants::gScreenWidth - rect.w;
                velocity.x *= -elasticity;
            }

            if (position.y < 0)
            {
                position.y = 0;
                velocity.y *= -elasticity;
            }
            else if (position.y + rect.h > constants::gScreenHeight)
            {
                position.y = constants::gScreenHeight - rect.h;
                velocity.y *= -elasticity;
            }
        }

        // update bounding box based on new position
        updateRect();
    }

    bool PhysicsBody::isColliding(const PhysicsBody *other) const
    {
        return SDL_HasIntersection(&rect, &other->rect);
    }

    void PhysicsBody::resolveCollision(PhysicsBody *other)
    {
        // calculate the relative velocity of the two bodies
        float relativeVelocityX = velocity.x - other->velocity.x;
        float relativeVelocityY = velocity.y - other->velocity.y;

        // check if the bodies are moving towards each other
        bool movingTowards = (relativeVelocityX * (position.x - other->position.x) + relativeVelocityY * (position.y - other->position.y)) < 0;
        if (!movingTowards)
        {
            return;
        }

        // calculate the combined mass of the two bodies
        float combinedMass = mass + other->mass;

        // calculate the impulse to apply to the bodies to resolve the collision
        float impulseX = (1 + elasticity) * relativeVelocityX / combinedMass;
        float impulseY = (1 + elasticity) * relativeVelocityY / combinedMass;

        // apply the impulse to the bodies
        velocity.x -= impulseX * mass;
        velocity.y -= impulseY * mass;
        other->velocity.x += impulseX * other->mass;
        other->velocity.y += impulseY * other->mass;

        // update the bounding boxes of the bodies
        updateRect();
        other->updateRect();
    }

    void PhysicsBody::updateRect()
    {
        rect.x = static_cast<int>(position.x);
        rect.y = static_cast<int>(position.y);
    }

    void PhysicsBody::addForce(float x, float y)
    {
        velocity.x += x / mass;
        velocity.y += y / mass;
    }


} // fruitwork