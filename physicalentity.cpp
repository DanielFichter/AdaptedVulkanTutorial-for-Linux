#include "physicalentity.hpp"
#include "movingdirection.hpp"

#include <stdexcept>
#include <format>
#include <algorithm>
#include <iostream>
#include <vector>

std::optional<PhysicalEntity::Collision> PhysicalEntity::collide(const PhysicalEntity &other)
{    
    const std::vector<glm::length_t> dimensions{0, 1, 2};
    std::vector<FloatingPointType> overlapValues(3);
    std::transform(dimensions.begin(), dimensions.end(), overlapValues.begin(), [this, &other] (glm::length_t dimension) { return overlaps(other, dimension); });
    
    if (std::all_of(overlapValues.begin(), overlapValues.end(), [] (FloatingPointType value) { return value; }))
    {
        const glm::length_t collisionDimension = *std::min_element(dimensions.begin(), dimensions.end(), [overlapValues] (glm::length_t dimension1, glm::length_t dimension2) { return std::abs(overlapValues.at(dimension1)) < std::abs(overlapValues.at(dimension2)); });
        return {Collision{collisionDimension, *this, overlapValues.at(collisionDimension) > 0.f ? 1.f : -1.f}};
    }
    return {};
}

void PhysicalEntity::fall(float dt)
{
    verticalSpeed += fallingAcceleration * dt;
    const glm::vec4 upAxis = directionToAxis.at(MovingDirection::up);
    position += glm::vec3{upAxis} * verticalSpeed * dt;
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

FloatingPointType PhysicalEntity::overlaps(const PhysicalEntity &other, glm::length_t dimension) const
{
    if (dimension > 2)
    {
        throw std::runtime_error(std::format("dimension is {}, but is not allowed to be more than 2", dimension));
    }
    const auto minusBoundary = position[dimension] - size[dimension] / 2;
    const auto otherMinusBoundary = other.position[dimension] - other.size[dimension] / 2;
    const auto plusBoundary = position[dimension] + size[dimension] / 2;
    const auto otherPlusBoundary = other.position[dimension] + other.size[dimension] / 2;
    if (plusBoundary >= otherMinusBoundary && minusBoundary <= otherPlusBoundary)
    {
        if (plusBoundary - otherMinusBoundary < otherPlusBoundary - minusBoundary)
        {
            return otherMinusBoundary - plusBoundary;
        }
        else
        {
            return otherPlusBoundary - minusBoundary;
        }
    }
    return 0.f;
}