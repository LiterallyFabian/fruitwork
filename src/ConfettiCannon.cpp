#include <random>
#include <algorithm>
#include <SDL_image.h>
#include <thread>
#include "ConfettiCannon.h"
#include "Constants.h"
#include "System.h"

namespace fruitwork
{
    ConfettiCannon *fruitwork::ConfettiCannon::getInstance(int x, int y, int w, int h, const std::string &texturePath)
    {
        return new ConfettiCannon(x, y, w, h, texturePath);
    }

    void fruitwork::ConfettiCannon::draw() const
    {
        for (auto &c: confetti)
        {
            if (c == nullptr || !c->started)
                continue;

            c->sprite->draw();
        }
    }

    void fruitwork::ConfettiCannon::update(float elapsedTime)
    {
        for (auto &c: confetti)
        {
            if (c == nullptr) // not optimal but to prevent segfaults
                continue;

            // start if not started & time has passed
            if (!c->started)
            {
                if (SDL_GetTicks64() >= c->startTime)
                {
                    c->started = true;
                    c->sprite->getPhysicsBody()->addForce(c->force.x, c->force.y);
                    if (c->fadeOutTime != -1)
                        c->sprite->fadeOut(c->fadeOutTime, 200);
                }
                else
                {
                    continue;
                }
            }

            c->sprite->update(elapsedTime);

            if (c->startTime + 7000 < SDL_GetTicks64())
            {
                delete c->sprite;
                c = nullptr;
            }
        }
    }

    ConfettiCannon::ConfettiCannon(int x, int y, int w, int h, const std::string &texturePath) : Component(x, y, w, h)
    {
        texture = IMG_LoadTexture(sys.getRenderer(), texturePath.c_str());
    }

    void ConfettiCannon::fire(float angle, int spread, int amount, int time, int fadeOutTime)
    {
        for (int i = 0; i < amount; i++)
        {
            std::random_device rd;
            std::mt19937 g(rd());
            std::uniform_int_distribution<int> dist(0, colors.size() - 1);
            SDL_Color c = colors[dist(g)];

            SDL_Rect r = getRect();
            PhysicsBody *b = PhysicsBody::getInstance(r);
            b->setGravity(2);

            auto *conf = new Confetti();
            conf->sprite = Sprite::getInstance(r.x, r.y, r.w, r.h, texture);
            conf->sprite->setPhysicsBody(b);
            conf->sprite->setColorMod(c);
            conf->sprite->setAngle(rand() % 360);
            conf->startTime = SDL_GetTicks64() + (time / amount) * i;
            conf->fadeOutTime = fadeOutTime;

            // add force towards the angle with a random spread
            float iAngle = angle - spread / 2.0f + rand() % spread;
            float forceX = cosf(iAngle * M_PI / 180) * 1000;
            float forceY = sinf(iAngle * M_PI / 180) * 2000;
            conf->force = {forceX, forceY};

            confetti.push_back(conf);
        }
    }

    ConfettiCannon::~ConfettiCannon()
    {
        for (auto &c: confetti)
            delete c;

        SDL_DestroyTexture(texture);
    }

} // fruitwork