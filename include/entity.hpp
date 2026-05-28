#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <math.hpp>
#include <graphics.hpp>
#include <memory>

namespace EcoSim
{
    class EntityManager;

    class Entity
    {
        friend class EntityManager;

    public:
        Entity(const Entity &) = delete;
        Entity &operator=(const Entity &) = delete;

        Entity() = default;
        virtual ~Entity() = default;

        Vector2 position;

        virtual void update(float dt) = 0;
        virtual void render() = 0;

        int id() const { return id_; }
        void setId(int newId) { id_ = newId; }

        bool alive() const { return isAlive; }

        std::shared_ptr<Graphics> graphics;

    protected:
        bool isAlive = true;

        std::shared_ptr<EntityManager> entityManager;

    private:
        int id_ = 0;
    };
}

#endif