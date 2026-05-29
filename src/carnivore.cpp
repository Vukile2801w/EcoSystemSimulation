#include <herbivore.hpp>
#include <carnivore.hpp>
#include <math.hpp>
#include <creature.hpp>
#include <entityManager.hpp>
#include <iostream>

namespace EcoSim
{

    void Carnivore::update(float dt)
    {
        Creature::update(dt);
        this->stats.energy = max(0.0f, stats.energy - dt); // Passive energy drain
    }

    void Carnivore::render()
    {
        if (!isAlive)
            return;

        Color overlayColor;
        switch (currentAction)
        {
        case CreatureAction::Eat:
            overlayColor = Color(255, 255, 0); // Yellow overlay when eating
            break;
        case CreatureAction::Reproduce:
            overlayColor = Color(0, 255, 255); // Cyan overlay when reprodu
            break;
        case CreatureAction::Flee:
            overlayColor = Color(255, 0, 0); // Red overlay when fleeing
            break;
        case CreatureAction::Wander:
            overlayColor = Color(255, 0, 255); // Magenta overlay when wandering
        default:
            overlayColor = Color(0, 255, 0); // Green overlay for other actions
            break;
        }

        if (stats.energy < stats.maxEnergy * 0.3f)
        {
            overlayColor = Color(255, 255, 255); // White overlay when energy is low
        }
        if (stats.health < stats.maxHealth * 0.3f)
        {
            overlayColor = Color(0, 0, 0); // Black overlay when health is low
        }

        graphics->drawCircle(position, 12.0f, overlayColor);
        graphics->drawCircle(position, 10.0f, getColor());
    }

    void Carnivore::spawnChild(const CreatureStats &childStats)
    {
        Vector2 childPosition = position; // Spawn child at parent's position
        entityManager->createEntity<Carnivore>(
            childPosition,
            childStats);
    }

    CreatureAction Carnivore::scoreActions()
    {

        float EAT_BIAS = 1.5f;       // Bias towards eating when energy is low
        float REPRODUCE_BIAS = 1.0f; // Bias towards reproducing when energy is sufficient
        float WANDER_BIAS = 0.4f;    // Bias towards wandering when energy is sufficient
        float FLEE_BIAS = 0.0f;      // Carnivores don't flee, so no bias for fleeing

        if (!this->isActionDone && !this->isActionStarted)
        {
            switch (this->currentAction)
            {
            case CreatureAction::Eat:
                EAT_BIAS *= 2.0f; // Increase bias if currently eating
                break;
            case CreatureAction::Reproduce:
                REPRODUCE_BIAS *= 2.0f; // Increase bias if currently reproducing
                break;
            case CreatureAction::Flee:
                FLEE_BIAS *= 2.0f; // Increase bias if currently fleeing
                break;
            }
        }

        std::unordered_map<CreatureAction, float> actionScores;

        std::vector<std::shared_ptr<Herbivore>> nearbyHerbivores = this->getCreaturesInVisionRangeOfType<Herbivore>();
        std::vector<std::shared_ptr<Carnivore>> nearbyCarnivores = this->getCreaturesInVisionRangeOfType<Carnivore>();
        float distanceToClosestCarnivore = std::numeric_limits<float>::max();
        std::shared_ptr<Carnivore> closestMate = nullptr;
        for (const auto &carnivore : nearbyCarnivores)
        {
            float distance = position.dist(carnivore->position);
            if (distance < distanceToClosestCarnivore)
            {
                distanceToClosestCarnivore = distance;
                closestMate = carnivore;
            }
        }
        float distanceToClosestHerbivore = std::numeric_limits<float>::max();
        for (const auto &carnivore : nearbyHerbivores)
        {
            float distance = position.dist(carnivore->position);
            if (distance < distanceToClosestHerbivore)
            {
                distanceToClosestHerbivore = distance;
            }
        }

        float hunger =
            1.0f - (stats.energy / stats.maxEnergy);

        float preyDistanceScore = 1.0f;

        if (!nearbyHerbivores.empty())
        {
            preyDistanceScore =
                2.0f -
                clamp(
                    distanceToClosestHerbivore / stats.visionRange,
                    0.0f,
                    1.0f);
        }

        actionScores[CreatureAction::Eat] =
            easeInOut(hunger) *
            preyDistanceScore *
            EAT_BIAS;

        actionScores[CreatureAction::Reproduce] =
            easeInOut(stats.energy / stats.maxEnergy) * REPRODUCE_BIAS * (closestMate ? 1.0f : 0.0f) * (reproductionCooldown <= 0.0f ? 1.0f : 0.0f);

        actionScores[CreatureAction::Flee] = FLEE_BIAS;

        actionScores[CreatureAction::Wander] =
            WANDER_BIAS + random(0.0f, 0.3f);

        float maxScore = std::numeric_limits<float>::lowest();
        CreatureAction maxScoreAction = CreatureAction::Wander;
        for (const auto &[action, score] : actionScores)
        {
            if (score > maxScore)
            {
                maxScore = score;
                maxScoreAction = action;
            }
        }

        return maxScoreAction;
    }

    void Carnivore::performAction(CreatureAction action, float dt)
    {
        switch (action)
        {
        case CreatureAction::Eat:
        {
            std::vector<std::shared_ptr<Herbivore>> nearbyHerbivores =
                this->getCreaturesInVisionRangeOfType<Herbivore>();

            float distanceToClosestHerbivore =
                std::numeric_limits<float>::max();

            std::shared_ptr<Herbivore> closestPrey = nullptr;

            for (const auto &herbivore : nearbyHerbivores)
            {
                float distance = position.dist(herbivore->position);

                if (distance < distanceToClosestHerbivore)
                {
                    distanceToClosestHerbivore = distance;
                    closestPrey = herbivore;
                }
            }

            if (closestPrey)
            {
                if (position.dist(closestPrey->position) < 5.0f)
                {
                    // Eat the prey
                    stats.energy =
                        min(stats.maxEnergy,
                            stats.energy + closestPrey->stats.health + 20.0f);

                    closestPrey->isAlive = false;

                    isActionDone = true;
                }
                else
                {
                    moveTowards(closestPrey->position, dt);
                    targetPosition = closestPrey->position; // Update target position to prey's current position
                }
            }
            else
            {
                if (position.dist(targetPosition) < 2.0f)
                {
                    float angle = random(0.0f, 6.28318f);
                    Vector2 dir(cos(angle), sin(angle));
                    Vector2 direction = ((targetPosition - position) + dir * 0.5f).normalize();

                    targetPosition = position + direction * 80.0f; // Update target position to new combination of wander and prey direction
                }
                else
                {
                    isActionDone = true;
                    isActionStarted = false;
                }
                moveToTarget(dt);
            }

            break;
        }

        case CreatureAction::Reproduce:
        {
            if (!isActionStarted)
            {
                std::vector<std::shared_ptr<Carnivore>> nearbyCarnivores =
                    this->getCreaturesInVisionRangeOfType<Carnivore>();

                std::shared_ptr<Carnivore> closestMate;

                float closestDistance =
                    std::numeric_limits<float>::max();

                for (const auto &carnivore : nearbyCarnivores)
                {
                    float distance = position.dist(carnivore->position);

                    if (distance < closestDistance &&
                        carnivore->reproductionCooldown <= 0.0f)
                    {
                        closestDistance = distance;
                        closestMate = carnivore;
                    }
                }

                this->creatureTarget = closestMate;

                isActionStarted = true;
            }

            if (!creatureTarget)
            {
                isActionDone = true;
                break;
            }

            if (position.dist(creatureTarget->position) < 5.0f)
            {
                Reproduce(creatureTarget);
                isActionDone = true;
            }
            else
            {
                moveTowards(creatureTarget->position, dt);
            }

            break;
        }

        case CreatureAction::Flee:
        {
            // Fleeing is not implemented for carnivores.
            break;
        }

        case CreatureAction::Wander:
        {
            if (!isActionStarted)
            {
                float angle = random(0.0f, 6.28318f);
                Vector2 dir(cos(angle), sin(angle));

                targetPosition = position + dir * 80.0f;

                isActionStarted = true;
            }

            Vector2 delta = targetPosition - position;

            if (delta.length() > 2.0f)
            {
                Vector2 direction = delta.normalize();

                position =
                    position + direction * stats.speed * dt;
            }
            else
            {
                isActionDone = true;
                isActionStarted = false;
            }

            break;
        }
        }
    }
}