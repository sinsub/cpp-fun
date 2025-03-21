#include "BouncingBalls.h"

#include "util/Random.h"

static double flip(double val)
{
    return random(1.0) < 0.5 ? val : -val;
}

BouncingBalls::BouncingBalls(uint32_t count) : count(count)
{
    double pMin = RADIUS, pMax = LENGTH - RADIUS;
    double vMin = LENGTH / 60.0, vMax = LENGTH / 5.0;
    while (count-- > 0)
    {
        ECS::Entity disc = entityManager.createEntity();
        discs.push_back(disc);
        positions.addComponent(disc, {random(pMin, pMax), random(pMin, pMax)});
        velocities.addComponent(disc, {flip(random(vMin, vMax)), flip(random(vMin, vMax))});
    }
}

void BouncingBalls::update(double dt)
{
    for (ECS::Entity entity : discs)
    {
        Position2D *p = positions.getComponent(entity);
        Velocity2D *v = velocities.getComponent(entity);

        Position2D pp {};
        Velocity2D vv {};
        pp.x = p->x + v->vx * dt;
        pp.y = p->y + v->vy * dt;
        vv.vx = v->vx;
        vv.vy = v->vy;

        if (pp.x < RADIUS)
        {
            pp.x += RADIUS - pp.x;
            vv.vx *= -1;
        }
        else if (pp.x > LENGTH - RADIUS)
        {
            pp.x -= pp.x - (LENGTH - RADIUS);
            vv.vx *= -1;
        }


        if (pp.y < RADIUS)
        {
            pp.y += RADIUS - pp.y;
            vv.vy *= -1;
        }
        else if (pp.y > LENGTH - RADIUS)
        {
            pp.y -= pp.y - (LENGTH - RADIUS);
            vv.vy *= -1;
        }

        positions.addComponent(entity, pp);
        velocities.addComponent(entity, vv);
    }
}

void BouncingBalls::draw(sf::RenderWindow &window)
{
    auto size = window.getSize();
    float radius = RADIUS * size.x;
    sf::CircleShape circle(radius);
    circle.setFillColor(sf::Color(0, 255, 255));
    for (auto entity: discs)
    {
        Position2D *pos = positions.getComponent(entity);
        float y = pos->y * size.y;
        y -= radius;
        float x = pos->x * size.x;
        x -= radius;
        circle.setPosition({x, y});
        window.draw(circle);
    }
}
