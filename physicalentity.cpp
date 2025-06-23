#include "physicalentity.hpp"
#include "movingdirection.hpp"

bool PhysicalEntity::collide(const PhysicalEntity &other)
{
    const auto leftBoundary = position.x - width / 2;
    const auto otherLeftBoundary = other.position.x - other.width / 2;
    const auto rightBoundary = position.x + width / 2;
    const auto otherRightBoundary = other.position.x + other.width / 2;
    const bool overlapX = rightBoundary >= otherLeftBoundary && leftBoundary <= otherRightBoundary;

    const auto upperBoundary = position.y + length / 2;
    const auto otherUpperBoundary = other.position.y + other.length / 2;
    const auto lowerBoundary = position.y - length / 2;
    const auto otherLowerBoundary = other.position.y - other.length / 2;
    const bool overlapY = upperBoundary >= otherLowerBoundary && lowerBoundary <= otherUpperBoundary;

    const auto frontBoundary = position.z + height / 2;
    const auto otherFrontBoundary = other.position.z + other.height / 2;
    const auto backBoundary = position.z - height / 2;
    const auto otherBackBoundary = other.position.z - other.height / 2;
    const bool overlapZ = frontBoundary >= otherBackBoundary && backBoundary <= otherFrontBoundary;

    return overlapX && overlapY && overlapZ;
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

PhysicalEntity::PhysicalEntity(const glm::vec3 &position, FloatingPointType width, FloatingPointType length, FloatingPointType height) : position{position}, width{width}, height{height}, length{length}
{
}

void PhysicalEntity::translate(const glm::vec3& offset)
{
    position += offset;
}