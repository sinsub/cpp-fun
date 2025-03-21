#pragma once

#include <cstdint>
#include <unordered_map>

namespace ECS {

using Entity = uint64_t;


class EntityManager {
public:
    Entity createEntity() { return nextId++; }
private:
    Entity nextId = 0u;
};


template <typename C>
class ComponentManager
{
public:
    void addComponent(Entity entity, C component) { store[entity] = component; }
    C *getComponent(Entity entity)
    {
        auto it = store.find(entity);
        if (it != store.end())
        {
            return &it->second;
        }
        return nullptr; // component not found
    }

private:
    std::unordered_map<Entity, C> store;
};


};
