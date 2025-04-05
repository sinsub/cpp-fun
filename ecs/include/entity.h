#ifndef ECS_ENTITY_H_
#define ECS_ENTITY_H_

#include <stdint.h>

#include <unordered_set>

namespace ecs {

using Entity = uint64_t;

class EntityManager {
   public:
    using Iterator = std::unordered_set<Entity>::const_iterator;

    EntityManager() = default;

    Entity create();
    bool erase(Entity entity);

    Iterator begin();
    Iterator end();

    // disable copying
    EntityManager(const EntityManager& that) = delete;
    EntityManager& operator=(const EntityManager& that) = delete;

   private:
    Entity next{0};
    std::unordered_set<Entity> entites{};
};

}  // namespace ecs

#endif
