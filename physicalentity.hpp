#pragma once

#include <glm/glm.hpp>
#include "floatingpointtype.hpp"

class PhysicalEntity
{
public:
    PhysicalEntity(const glm::vec3 &position, FloatingPointType width, FloatingPointType height, FloatingPointType length);
    bool collide(const PhysicalEntity &other);
    void fall(float dt);

protected:
    FloatingPointType verticalSpeed = 0;
    FloatingPointType fallingAcceleration = -.5;
    glm::vec3 position;
    FloatingPointType width;
    FloatingPointType height;
    FloatingPointType length;
};