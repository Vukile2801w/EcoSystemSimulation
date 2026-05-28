#ifndef CARNIVORE_HPP
#define CARNIVORE_HPP
#include <creature.hpp>
#include <math.hpp>

namespace EcoSim
{
    class Carnivore : public Creature
    {
    public:
        Carnivore(Vector2 position) : Creature(position) {}
        Carnivore(Vector2 position, CreatureStats stats) : Creature(position, stats) {}

        void render() override { Creature::render(); }
        void update(float dt) override;

        CreatureAction scoreActions() override;

    private:
        Color color = Color(0x751B72);
    };
}

#endif