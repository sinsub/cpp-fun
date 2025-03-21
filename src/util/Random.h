#pragma once

#include <random>

static std::mt19937 gen(std::random_device{}());
static std::uniform_real_distribution<> dis(0.0, 1.0);

inline double random(double high)
{
    return dis(gen) * high;
}

inline double random(double low, double high)
{
    return dis(gen) * (high - low) + low;
}
