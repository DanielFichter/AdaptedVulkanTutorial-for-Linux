#include "physicalentity.hpp"
#include "movingdirection.hpp"

bool PhysicalEntity::collide(const PhysicalEntity &other)
{
    const auto leftBoundary = position.x - width / 2;
    const auto otherLeftBoundary = other.position.x - other.width / 2;
    const auto rightBoundary = position.x + width / 2;
    const auto otherRightBoundary = other.position.x + other.width / 2;
    const bool overlapX = rightBoundary >= otherLeftBoundary && leftBoundary <= otherRightBoundary;

    const auto upperBoundary = position.y + height / 2;
    const auto otherUpperBoundary = other.position.y + other.height / 2;
    const auto lowerBoundary = position.y + height / 2;
    const auto otherLowerBoundary = other.position.y + other.height / 2;
    const bool overlapY = upperBoundary >= otherLowerBoundary && lowerBoundary <= otherUpperBoundary;

    const auto frontBoundary = position.z + length / 2;
    const auto otherFrontBoundary = other.position.z + other.length / 2;
    const auto backBoundary = position.z - length / 2;
    const auto otherBackBoundary = other.position.z - other.length / 2;
    const bool overlapZ = frontBoundary >= otherBackBoundary && backBoundary <= otherFrontBoundary;

    return overlapX && overlapY && overlapZ;
}

void PhysicalEntity::fall(float dt)
{
    verticalSpeed += fallingAcceleration * dt;
    const glm::vec4 downAxis = directionToAxis.at(MovingDirection::down);
    position += glm::vec3{downAxis} * verticalSpeed * dt;
}

PhysicalEntity::PhysicalEntity(const glm::vec3 &position, FloatingPointType width, FloatingPointType height, FloatingPointType length) : position{position}, width{width}, height{height}, length{length}
{
}
