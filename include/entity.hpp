#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <math.hpp>
#include <graphics.hpp>
#include <memory>

namespace EcoSim{
    class Entity
    {
    public:
        Entity(const Entity&) = delete; // Disable copy constructor
        Entity& operator=(const Entity&) = delete; // Disable copy assignment

        Entity() = default; // Default constructor
        ~Entity() = default; // Default destructor

        Vector2 position;
        virtual void update(float dt) = 0;
        virtual void render() = 0;

        int id() const { return id_; }
        void setId(int newId) { id_ = newId; }

        bool alive() const { return isAlive; }

        std::shared_ptr<Graphics> graphics; // Reference to the graphics system for rendering
        


    protected:
        bool isAlive = true; // Flag to indicate if the entity is alive

    private:
        int id_ = 0; // Unique identifier for the entity

    };
}

#endif // ENTITY_HPP