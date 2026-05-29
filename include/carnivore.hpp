#ifndef CARNIVORE_HPP
#define CARNIVORE_HPP
#include <creature.hpp>
#include <math.hpp>

namespace EcoSim
{
    class Carnivore : public Creature
    {
    public:
        Carnivore(Vector2 position) : Creature(position) { color = Color(0xD9534F); }
        Carnivore(Vector2 position, CreatureStats stats) : Creature(position, stats) { color = Color(0xD9534F); }

        void render() override;
        void update(float dt) override;

        CreatureAction scoreActions() override;
        void spawnChild(const CreatureStats &childStats) override;
        void performAction(CreatureAction action, float dt) override;
    };
}

#endif