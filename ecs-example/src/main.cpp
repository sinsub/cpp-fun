#include <stdio.h>

#include "ecs.h"

struct Position {
    int x, y;
};

int main() {
    printf("ECS version %s\n", ecs::GetVersion());
    ecs::EntityManager em{};
    ecs::ComponentManager<Position> cm{};

    ecs::Entity one = em.create();
    ecs::Entity two = em.create();
    ecs::Entity three = em.create();

    cm.addComponent(one, {1, 1});
    cm.addComponent(three, {3, 3});

    for (auto entity : em) {
        Position *pos = cm.getComponent(entity);
        if (pos)
            printf("Entity: %lu - Position{%d, %d}\n", entity, pos->x, pos->y);
        else
            printf("Entity: %lu - No Position Component\n", entity);
    }

    // TODO: this should remove components from ComponentManager
    em.erase(three);

    printf("Remove three\n");

    for (auto entity : em) {
        Position *pos = cm.getComponent(entity);
        if (pos)
            printf("Entity: %lu - Position{%d, %d}\n", entity, pos->x, pos->y);
        else
            printf("Entity: %lu - No Position Component\n", entity);
    }
}
