#pragma once

#include "axes.hpp"

#include <map>

enum class MovingDirection
{
    forward,
    backward,
    left,
    right,
    up,
    down,
    none
};

using enum MovingDirection;
const std::map<MovingDirection, glm::vec4> directionToAxis{{forward, Axes::y},
                                                     {left, -Axes::x},
                                                     {backward, -Axes::y},
                                                     {right, Axes::x},
                                                     {up, Axes::z},
                                                     {down, -Axes::z}};