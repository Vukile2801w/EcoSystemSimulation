#ifndef CREATURE_HPP
#define CREATURE_HPP

#include <Entity.hpp>
#include <creatureStats.hpp>
#include <colors.hpp>


namespace EcoSim
{
    class Creature : public Entity
    {
    public:
        CreatureStats stats;

        Creature(const Vector2& position, const CreatureStats& stats)
        {
            this->position = position;
            this->stats = stats;
        }
        Creature(const Vector2& position) {
            this->position = position;
            this->stats = CreatureStats(DEFAULT_CREATURE_STATS); // Use default stats
        }

        void update(float dt) override;
        void render() override;

    private:
        Color color = Color(255, 0, 255); // Default color (magenta)
    };
}

#endif // CREATURE_HPP