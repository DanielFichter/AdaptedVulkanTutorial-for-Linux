#pragma once

#include <glm/glm.hpp>
#include "floatingpointtype.hpp"

class PhysicalEntity
{
public:
    PhysicalEntity(const glm::vec3 &position, FloatingPointType width, FloatingPointType length, FloatingPointType height);
    virtual bool collide(const PhysicalEntity &other);
    virtual void fall(float dt);
    void restoreFalling();
    virtual void advance(float dt) {}
    const glm::vec3& getPosition() const { return position; }
    const glm::vec3 getSize() const { return {width, length, height}; }
    void place(const glm::vec3& newPosition);
    virtual void reset() {}
    virtual void translate(const glm::vec3&);
    FloatingPointType verticalSpeed = 0;
    
protected:
    
    FloatingPointType fallingAcceleration = -9;
    glm::vec3 position;
    FloatingPointType width;
    FloatingPointType height;
    FloatingPointType length;
    FloatingPointType lastFallHeight = 0;
};