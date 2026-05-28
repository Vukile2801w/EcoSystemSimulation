#ifndef CREATURE_STATS_HPP
#define CREATURE_STATS_HPP

namespace EcoSim
{

    /// Basic stats for a creature in the ecosystem simulation
    struct CreatureStats
    {
        CreatureStats() = default;                                                                           // Default empty constructor
        CreatureStats(float health, float energy, float speed, float visionRange, float age, float lifespan) // Default constructor with parameters
            : health(health), maxHealth(health), energy(energy), maxEnergy(energy), speed(speed), visionRange(visionRange), age(age), lifespan(lifespan)
        {
        }
        CreatureStats(const CreatureStats &other)
        { // Copy constructor
            health = other.health;
            maxHealth = other.maxHealth;
            energy = other.energy;
            maxEnergy = other.maxEnergy;
            speed = other.speed;
            visionRange = other.visionRange;
            age = other.age;
            lifespan = other.lifespan;
        };

        float health;    // Current health level
        float maxHealth; // Maximum health level (can be used for normalization)

        float energy;    // Current energy level
        float maxEnergy; // Maximum energy level (can be used for normalization)

        float speed;       // Movement speed in units per second
        float visionRange; // How far the creature can see in units

        float age;      // Current age in seconds
        float lifespan; // Maximum age before death in seconds
    };

    static const CreatureStats DEFAULT_CREATURE_STATS = {
        100.0f, // health
        100.0f, // energy
        50.0f,  // speed
        100.0f, // visionRange
        0.0f,   // age
        300.0f  // lifespan (5 minutes)
    };

}

#endif // CREATURE_STATS_HPP