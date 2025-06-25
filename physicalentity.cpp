#include "physicalentity.hpp"
#include "movingdirection.hpp"

#include <stdexcept>
#include <format>

bool PhysicalEntity::collide(const PhysicalEntity &other)
{
    return overlaps(other, 0) && overlaps(other, 1) && overlaps(other, 2);
}

void PhysicalEntity::fall(float dt)
{
    verticalSpeed += fallingAcceleration * dt;
    const glm::vec4 upAxis = directionToAxis.at(MovingDirection::up);
    lastFallHeight = verticalSpeed * dt;
    position += glm::vec3{upAxis} * lastFallHeight;
}

void PhysicalEntity::restoreFalling()
{
    const glm::vec4 upAxis = directionToAxis.at(MovingDirection::up);
    position -= glm::vec3{upAxis} * lastFallHeight;
}

void PhysicalEntity::place(const glm::vec3 & newPosition)
{
    position = newPosition;
    verticalSpeed = 0;
}

PhysicalEntity::PhysicalEntity(const glm::vec3 &position, const glm::vec3& size) : position{position}, size{size}
{
}

void PhysicalEntity::translate(const glm::vec3& offset)
{
    position += offset;
}

bool PhysicalEntity::overlaps(const PhysicalEntity &other, glm::length_t dimension) const
{
    if (dimension > 2)
    {
        throw std::runtime_error(std::format("dimension is {}, but is not allowed to be more than 2", dimension));
    }
    const auto leftBoundary = position[dimension] - size[dimension] / 2;
    const auto otherLeftBoundary = other.position[dimension] - other.size[dimension] / 2;
    const auto rightBoundary = position[dimension] + size[dimension] / 2;
    const auto otherRightBoundary = other.position[dimension] + other.size[dimension] / 2;
    return rightBoundary >= otherLeftBoundary && leftBoundary <= otherRightBoundary;
}