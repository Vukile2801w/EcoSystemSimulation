#ifndef HERBIVORE_HPP
#define HERBIVORE_HPP
#include <creature.hpp>
#include <math.hpp>

namespace EcoSim
{
    class Herbivore : public Creature
    {
    public:
        Herbivore(Vector2 position) : Creature(position) { color = Color(0x6BCB77); }
        Herbivore(Vector2 position, CreatureStats stats) : Creature(position, stats) { color = Color(0x6BCB77); }

        void render() override;
        void update(float dt) override;

        CreatureAction scoreActions() override;
        void spawnChild(const CreatureStats &childStats) override;
        void performAction(CreatureAction action, float dt) override;
    };
}

#endif