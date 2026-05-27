#ifndef ENTITY_MANAGER_HPP
#define ENTITY_MANAGER_HPP

#include <algorithm>
#include <memory>
#include <vector>
#include <Entity.hpp>
#include <time.hpp>

namespace EcoSim
{
    class EntityManager
    {
    public:
        EntityManager(std::shared_ptr<Graphics> graphics, std::shared_ptr<Time> time)
        {
            this->graphics = graphics;
            this->time = time;

            this->graphics->addUpdateCallback([this]()
                                              { updateAll(); }); // Register update callback
            this->graphics->addDrawCallback([this]()
                                            { renderAll(); }); // Register draw callback
        }
        ~EntityManager() = default;

        template <typename EntityType, typename... Args>
        std::shared_ptr<EntityType> createEntity(Args &&...args)
        {
            auto entity = std::make_shared<EntityType>(std::forward<Args>(args)...);
            entity->setId(nextId_++);
            entity->graphics = graphics; // Set graphics reference for the entity
            entities_.push_back(entity);
            return entity;
        }

        void addEntity(const std::shared_ptr<Entity> &entity)
        {
            if (entity)
            {
                entities_.push_back(entity);
            }
        }

        void removeEntityById(int id)
        {
            entities_.erase(
                std::remove_if(entities_.begin(), entities_.end(), [id](const std::shared_ptr<Entity> &entity)
                               { return entity && entity->id() == id; }),
                entities_.end());
        }

        std::shared_ptr<Entity> getEntityById(int id) const
        {
            auto it = std::find_if(entities_.begin(), entities_.end(), [id](const std::shared_ptr<Entity> &entity)
                                   { return entity && entity->id() == id; });
            return it != entities_.end() ? *it : nullptr;
        }

        void updateAll()
        {
            for (const auto &entity : entities_)
            {
                if (entity && entity->alive())
                {
                    entity->update(time->GetDeltaTime());
                }
            }

            entities_.erase(
                std::remove_if(
                    entities_.begin(),
                    entities_.end(),
                    [](const std::shared_ptr<Entity> &e)
                    {
                        return !e || !e->alive();
                    }),
                entities_.end());
        }

        void renderAll()
        {
            for (const auto &entity : entities_)
            {
                if (entity && entity->alive())
                {
                    entity->render();
                }
            }
        }

        const std::vector<std::shared_ptr<Entity>> &entities() const
        {
            return entities_;
        }

    private:
        std::vector<std::shared_ptr<Entity>> entities_;
        int nextId_ = 1;

        std::shared_ptr<Time> time;
        std::shared_ptr<Graphics> graphics;
    };

} // namespace EcoSystemSimulation

#endif // ECOSYSTEMSIMULATION_ENTITY_MANAGER_HPP
