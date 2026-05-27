#include <creature.hpp>
#include <raylib/raylibGraphics.hpp>
#include <iostream>

namespace EcoSim
{
    void Creature::update(float dt)
    {
         this->stats.age += dt;
        if (this->stats.age >= this->stats.lifespan)
        {
            
        }
    }

    void Creature::render()
    {
        graphics->drawCircle(position, 10.0f, color);
    }
}