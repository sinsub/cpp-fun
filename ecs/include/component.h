#ifndef ECS_COMPONENT_H_
#define ECS_COMPONENT_H_

#include <entity.h>

#include <unordered_map>

namespace ecs {

template <typename Component>
class ComponentManager {
   public:
    void addComponent(Entity entity, Component component) { map[entity] = component; }
    void removeComponent(Entity entity) { map.erase(entity); }
    bool hasComponent(Entity entity) { return map.find() != map.end(); }
    Component *getComponent(Entity entity) {
        auto it = map.find(entity);
        if (it != map.end()) {
            return &(it->second);
        }
        return nullptr;
    }

   private:
    std::unordered_map<Entity, Component> map{};
};

}  // namespace ecs

#endif