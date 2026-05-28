#ifndef ENTITY_MANAGER_HPP
#define ENTITY_MANAGER_HPP

#include <memory>
#include <vector>

namespace EcoSim
{
    class Entity;
    class Graphics;
    class Time;

    class EntityManager : public std::enable_shared_from_this<EntityManager>
    {
    public:
        EntityManager(std::shared_ptr<Graphics> graphics,
                      std::shared_ptr<Time> time);

        ~EntityManager() = default;

        template <typename EntityType, typename... Args>
        std::shared_ptr<EntityType> createEntity(Args &&...args)
        {
            auto entity = std::make_shared<EntityType>(
                std::forward<Args>(args)...);

            entity->setId(nextId_++);
            entity->graphics = graphics;
            entity->entityManager = shared_from_this();

            entities_.push_back(entity);

            return entity;
        }

        void addEntity(const std::shared_ptr<Entity> &entity);

        void removeEntityById(int id);

        std::shared_ptr<Entity> getEntityById(int id) const;

        void updateAll();

        void renderAll();

        const std::vector<std::shared_ptr<Entity>> &entities() const;

    private:
        std::vector<std::shared_ptr<Entity>> entities_;

        int nextId_ = 1;

        std::shared_ptr<Time> time;
        std::shared_ptr<Graphics> graphics;
    };

} // namespace EcoSim

#endif // ENTITY_MANAGER_HPP