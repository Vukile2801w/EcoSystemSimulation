#ifndef CREATURE_HPP
#define CREATURE_HPP

#include <Entity.hpp>
#include <creatureStats.hpp>
#include <colors.hpp>
#include <math.hpp>
namespace EcoSim
{
    enum class CreatureAction
    {
        Wander,
        Eat,
        Reproduce,
        Idle,
        Flee,
        Count
    };

    class Creature : public Entity
    {
    public:
        CreatureStats stats;

        Creature(const Vector2 &position, const CreatureStats &stats)
        {
            this->position = position;
            this->stats = stats;
        }
        Creature(const Vector2 &position)
        {
            this->position = position;
            this->stats = CreatureStats(DEFAULT_CREATURE_STATS); // Use default stats
        }

        virtual void update(float dt) override;
        virtual void render() override;

        virtual CreatureAction scoreActions();
        virtual void performAction(CreatureAction action, float dt);

        virtual void moveTowards(const Vector2 &target, float dt);
        virtual void moveToTarget(float dt);

        virtual void Reproduce(std::shared_ptr<Creature> other);
        virtual void spawnChild(const CreatureStats &childStats);

        virtual std::vector<std::shared_ptr<Creature>> getCreaturesInVisionRange();

        template <typename T>
        std::vector<std::shared_ptr<T>>
        getCreaturesInVisionRangeOfType()
        {
            std::vector<std::shared_ptr<T>> result;

            for (const auto &creature : getCreaturesInVisionRange())
            {
                auto casted = std::dynamic_pointer_cast<T>(creature);

                if (casted && casted.get() != this)
                {
                    result.push_back(casted);
                }
            }

            return result;
        }

        CreatureAction currentAction = CreatureAction::Wander;
        bool isActionDone = true;
        bool isActionStarted = false;
        std::shared_ptr<Creature> creatureTarget;
        Vector2 targetPosition;
        bool isAlive = true;               // Flag to indicate if the creature is alive
        float timer = 0.0f;                // Timer for managing action durations
        float reproductionCooldown = 1.0f; // Cooldown timer for reproduction in seconds

        virtual Color getColor() const { return color; }

    protected:
        Color color = Color(255, 0, 255); // Default magenta color for creatures
    };
}

#endif // CREATURE_HPP