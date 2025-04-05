#include "entity.h"

namespace ecs {

Entity EntityManager::create() {
    Entity e = next++;
    entites.insert(e);
    return e;
}

bool EntityManager::erase(Entity entity) { return entites.erase(entity) > 0; }

EntityManager::Iterator EntityManager::begin() { return entites.begin(); }

EntityManager::Iterator EntityManager::end() { return entites.end(); }

}  // namespace ecs
