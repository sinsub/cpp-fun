#include <stdio.h>

#include "ecs.h"

int main() {
    printf("ECS version %s\n", ecs::GetVersion());
    ecs::EntityManager em{};
    ecs::Entity one = em.create();
    ecs::Entity two = em.create();
    ecs::Entity three = em.create();
    em.erase(two);
    for (auto entity : em) {
        printf("Entity: %lu\n", entity);
    }
}
