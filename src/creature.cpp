#include <creature.hpp>
#include <entityManager.hpp>
#include <raylib/raylibGraphics.hpp>
#include <iostream>
#include <math.hpp>

namespace EcoSim
{

    void Creature::update(float dt)
    {
        this->stats.age += dt;
        if (this->stats.age >= this->stats.lifespan)
        {
            this->isAlive = false; // Mark creature as dead
            return;
        }
        if (this->stats.health <= 0.0f)
        {
            this->isAlive = false; // Mark creature as dead
            return;
        }
        if (this->stats.energy <= 0.0f)
        {
            this->stats.health -= dt * 0.5f; // Mark creature as dead
            return;
        }

        this->reproductionCooldown -= dt;
        this->reproductionCooldown = max(0.0f, this->reproductionCooldown);

        CreatureAction newAction = scoreActions();

        if (newAction != currentAction)
        {
            currentAction = newAction;

            isActionStarted = false;
            isActionDone = false;
        }

        performAction(currentAction, dt);
    }

    CreatureAction Creature::scoreActions()
    {
        return CreatureAction::Wander; // Shoud be implemented in child classes, this is just a placeholder.
    }

    void Creature::performAction(CreatureAction action, float dt)
    {
        switch (action)
        {
        case CreatureAction::Wander:
            // Simple wandering behavior: move in a random direction
            if (timer <= 0.0f)
            {
                float angle = random(0.0f, 2.0f * 3.14159f);
                targetPosition = position + Vector2(cos(angle), sin(angle)) * 50.0f; // Move 50 units in the random direction
                timer = 10.0f;                                                       // Reset timer
            }
            else
            {
                timer -= dt;
                Vector2 direction = (targetPosition - position).normalize();
                position = position + direction * stats.speed * dt;
            }
            break;
        }
    }

    std::vector<std::shared_ptr<Creature>>
    Creature::getCreaturesInVisionRange()
    {
        std::vector<std::shared_ptr<Creature>> creatures;

        for (const auto &entity : entityManager->entities())
        {
            if (entity)
            {
                auto creature =
                    std::dynamic_pointer_cast<Creature>(entity);

                if (creature && creature.get() != this)
                {
                    float distance =
                        position.dist(creature->position);

                    if (distance <= stats.visionRange)
                    {
                        creatures.push_back(creature);
                    }
                }
            }
        }

        return creatures;
    }

    void Creature::render()
    {
        graphics->drawCircle(position, 10.0f, getColor());
    }

    void Creature::moveTowards(const Vector2 &target, float dt)
    {
        Vector2 direction = (position * -1 + target).normalize();
        position = position + direction * stats.speed * dt;

        stats.energy = max(
            0.0f,
            stats.energy - dt * stats.speed * 0.1f);
    }

    void Creature::moveToTarget(float dt)
    {
        if (position.dist(targetPosition) > 1.0f)
        {
            moveTowards(targetPosition, dt);
        }
    }

    void Creature::Reproduce(std::shared_ptr<Creature> other)
    {
        CreatureStats childStats = CreatureStats();

        childStats.health = random(stats.health, other->stats.health);
        childStats.energy = random(stats.energy, other->stats.energy);
        childStats.speed = random(stats.speed, other->stats.speed);
        childStats.visionRange = random(stats.visionRange, other->stats.visionRange);
        childStats.lifespan = random(stats.lifespan, other->stats.lifespan);

        float mutationChance = 0.3f; // 30% chance for mutation
        float mutationRate = 0.1f;   // Mutation can change stats by up to 10%

        if (random(0.0f, 1.0f) < mutationChance)
            childStats.health *= 1.0f + random(-mutationRate, mutationRate);

        if (random(0.0f, 1.0f) < mutationChance)
            childStats.energy *= 1.0f + random(-mutationRate, mutationRate);

        if (random(0.0f, 1.0f) < mutationChance)
            childStats.speed *= 1.0f + random(-mutationRate, mutationRate);

        if (random(0.0f, 1.0f) < mutationChance)
            childStats.visionRange *= 1.0f + random(-mutationRate, mutationRate);

        if (random(0.0f, 1.0f) < mutationChance)
            childStats.lifespan *= 1.0f + random(-mutationRate, mutationRate);

        this->reproductionCooldown = 20.0f;  // Set reproduction cooldown for the parent
        other->reproductionCooldown = 20.0f; // Set reproduction cooldown for the parent

        this->stats.energy = max(0.0f, stats.energy - 30.0f);         // Energy cost for reproduction
        other->stats.energy = max(0.0f, other->stats.energy - 30.0f); // Energy cost for reproduction

        spawnChild(childStats);
    }
    void Creature::spawnChild(const CreatureStats &childStats)
    {
        Vector2 childPosition = position; // Spawn child at parent's position
        entityManager->createEntity<Creature>(
                         childPosition,
                         childStats)
            ->reproductionCooldown = 20.0f; // Set reproduction cooldown for the child
    }
}