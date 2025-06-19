#pragma once

#include <glm/glm.hpp>
#include "floatingpointtype.hpp"

class PhysicalEntity
{
public:
    PhysicalEntity(const glm::vec3 &position, FloatingPointType width, FloatingPointType length, FloatingPointType height);
    bool collide(const PhysicalEntity &other);
    void fall(float dt);
    void restoreFalling();

protected:
    FloatingPointType verticalSpeed = 0;
    FloatingPointType fallingAcceleration = -1;
    glm::vec3 position;
    FloatingPointType width;
    FloatingPointType height;
    FloatingPointType length;
    FloatingPointType lastFallHeight = 0;
};