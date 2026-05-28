#include <entityManager.hpp>

#include <Entity.hpp>
#include <graphics.hpp>
#include <time.hpp>

#include <algorithm>

namespace EcoSim
{

    EntityManager::EntityManager(std::shared_ptr<Graphics> graphics,
                                 std::shared_ptr<Time> time)
    {
        this->graphics = graphics;
        this->time = time;

        this->graphics->addUpdateCallback([this]()
                                          { updateAll(); });

        this->graphics->addDrawCallback([this]()
                                        { renderAll(); });
    }

    void EntityManager::addEntity(const std::shared_ptr<Entity> &entity)
    {
        if (entity)
        {
            entities_.push_back(entity);
        }
    }

    void EntityManager::removeEntityById(int id)
    {
        entities_.erase(
            std::remove_if(
                entities_.begin(),
                entities_.end(),
                [id](const std::shared_ptr<Entity> &entity)
                {
                    return entity && entity->id() == id;
                }),
            entities_.end());
    }

    std::shared_ptr<Entity> EntityManager::getEntityById(int id) const
    {
        auto it = std::find_if(
            entities_.begin(),
            entities_.end(),
            [id](const std::shared_ptr<Entity> &entity)
            {
                return entity && entity->id() == id;
            });

        return it != entities_.end() ? *it : nullptr;
    }

    void EntityManager::updateAll()
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

    void EntityManager::renderAll()
    {
        for (const auto &entity : entities_)
        {
            if (entity && entity->alive())
            {
                entity->render();
            }
        }
    }

    const std::vector<std::shared_ptr<Entity>> &
    EntityManager::entities() const
    {
        return entities_;
    }

} // namespace EcoSim