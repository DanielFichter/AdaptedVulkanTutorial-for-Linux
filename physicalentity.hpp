#pragma once

#include <glm/glm.hpp>
#include "floatingpointtype.hpp"

class PhysicalEntity
{
public:
    PhysicalEntity(const glm::vec3 &position, const glm::vec3& size);
    virtual bool collide(const PhysicalEntity &other);
    virtual void fall(float dt);
    void restoreFalling();
    virtual void advance(float dt) {}
    const glm::vec3& getPosition() const { return position; }
    const glm::vec3 getSize() const { return size; }
    void place(const glm::vec3& newPosition);
    virtual void reset() {}
    virtual void translate(const glm::vec3&);
    FloatingPointType verticalSpeed = 0;

protected:
    bool overlaps(const PhysicalEntity& other, glm::length_t dimension) const;
    FloatingPointType fallingAcceleration = -9;
    glm::vec3 position;
    glm::vec3 size;
    FloatingPointType lastFallHeight = 0;
};