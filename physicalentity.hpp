#pragma once

#include "floatingpointtype.hpp"

#include <glm/glm.hpp>

#include <optional>

class PhysicalEntity
{
protected:
    struct Collision
    {
        glm::length_t dimension;
        const PhysicalEntity& physicalEntity;
        float sign;
    };

public:
    PhysicalEntity(const glm::vec3 &position, const glm::vec3& size);
    virtual std::optional<Collision> collide(const PhysicalEntity &other);
    virtual void fall(float dt);
    virtual void advance(float dt) {}
    const glm::vec3& getPosition() const { return position; }
    const glm::vec3 getSize() const { return size; }
    void place(const glm::vec3& newPosition);
    virtual void reset() {}
    virtual void translate(const glm::vec3&);
    FloatingPointType verticalSpeed = 0;

protected:
    FloatingPointType overlaps(const PhysicalEntity& other, glm::length_t dimension) const;
    FloatingPointType fallingAcceleration = -9;
    glm::vec3 position;
    glm::vec3 size;
};