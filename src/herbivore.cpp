#include <herbivore.hpp>
#include <carnivore.hpp>
#include <math.hpp>
#include <creature.hpp>
#include <entityManager.hpp>
#include <iostream>

namespace EcoSim
{

    void Herbivore::update(float dt)
    {
        Creature::update(dt);
        this->stats.energy = max(0.0f, stats.energy - dt); // Passive energy drain
    }

    void Herbivore::render()
    {
        graphics->drawCircle(position, 10.0f, getColor());
    }

    void Herbivore::spawnChild(const CreatureStats &childStats)
    {
        Vector2 childPosition = position; // Spawn child at parent's position
        entityManager->createEntity<Herbivore>(
            childPosition,
            childStats);
    }

    CreatureAction Herbivore::scoreActions()
    {

        float EAT_BIAS = 1.5f;       // Bias towards eating when energy is low
        float REPRODUCE_BIAS = 1.0f; // Bias towards reproducing when energy is sufficient
        float WANDER_BIAS = 0.4f;    // Bias towards wandering when energy is sufficient
        float FLEE_BIAS = 3.5f;      // Bias towards fleeing when health is low

        if (!this->isActionDone && !this->isActionDone)
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
        for (const auto &carnivore : nearbyCarnivores)
        {
            float distance = position.dist(carnivore->position);
            if (distance < distanceToClosestCarnivore)
            {
                distanceToClosestCarnivore = distance;
            }
        }

        actionScores[CreatureAction::Eat] = (1.0f - easeInOut((stats.energy / stats.maxEnergy))) * EAT_BIAS;

        actionScores[CreatureAction::Reproduce] =
            easeInOut(stats.energy / stats.maxEnergy) * REPRODUCE_BIAS * (!nearbyHerbivores.empty() ? 1.0f : 0.0f) * (reproductionCooldown <= 0.0f ? 1.0f : 0.0f);

        float fleeScore = 0.0f;

        if (!nearbyCarnivores.empty())
        {
            float normalizedDistance =
                1.0f - clamp(
                           distanceToClosestCarnivore / stats.visionRange,
                           0.0f,
                           1.0f);

            fleeScore =
                easeOutQuad(normalizedDistance) * FLEE_BIAS;
        }
        float fear =
            (2.0f - stats.health / stats.maxHealth); // Higher fear when health is low

        actionScores[CreatureAction::Flee] = fleeScore * fear;

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

    void Herbivore::performAction(CreatureAction action, float dt)
    {
        switch (action)
        {
        case CreatureAction::Eat:
            if (!isActionStarted)
            {
                float searchRadius = 120.0f;
                this->targetPosition = Vector2(position.x + random(-searchRadius, searchRadius), position.y + random(-searchRadius, searchRadius));
                isActionStarted = true;
            }

            if (!isActionDone)
            {
                if (position.dist(targetPosition) < 5.0f)
                {
                    stats.energy = min(stats.energy + 20.0f, stats.maxEnergy);

                    if (timer <= 0.0f)
                    {
                        isActionDone = true;
                    }
                    else
                    {
                        timer -= dt;
                    }
                }
                else
                {
                    timer = 5.0f; // Time taken to eat
                    moveToTarget(dt);
                }
            }
            break;

        case CreatureAction::Reproduce:

            if (!isActionStarted)
            {
                std::vector<std::shared_ptr<Herbivore>> nearbyHerbivores = this->getCreaturesInVisionRangeOfType<Herbivore>();
                std::shared_ptr<Herbivore> closestMate;
                float closestDistance = std::numeric_limits<float>::max();
                for (const auto &herbivore : nearbyHerbivores)
                {
                    float distance = position.dist(herbivore->position);
                    if (distance < closestDistance && herbivore->reproductionCooldown <= 0.0f)
                    {
                        closestDistance = distance;
                        closestMate = herbivore;
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

        case CreatureAction::Flee:
            if (!isActionStarted)
            {
                std::vector<std::shared_ptr<Carnivore>> nearbyCarnivores = this->getCreaturesInVisionRangeOfType<Carnivore>();
                std::shared_ptr<Carnivore> closestThreat;
                float closestDistance = std::numeric_limits<float>::max();
                for (const auto &carnivore : nearbyCarnivores)
                {
                    float distance = position.dist(carnivore->position);
                    if (distance < closestDistance)
                    {
                        closestDistance = distance;
                        closestThreat = carnivore;
                    }
                }

                if (closestThreat)
                {
                    Vector2 delta = position - closestThreat->position;

                    Vector2 fleeDirection;

                    if (delta.length() > 0.001f)
                    {
                        fleeDirection = delta.normalize();
                    }
                    else
                    {
                        fleeDirection = Vector2(1.0f, 0.0f); // fallback direction
                    }

                    this->targetPosition =
                        position + fleeDirection * 160.0f;
                }
                else
                {
                    this->targetPosition = position; // No threat found, stay in place
                }

                isActionStarted = true;
            }

            if (!isActionDone)
            {
                if (position.dist(targetPosition) < 5.0f)
                {
                    isActionDone = true;
                }
                else
                {
                    moveToTarget(dt);
                }
            }
            break;

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
                position = position + direction * stats.speed * dt;
                graphics->drawCircle(targetPosition, 10.0f, Color(255, 255, 0));
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