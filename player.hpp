#pragma once

#include "physicalentity.hpp"
#include "movingdirection.hpp"

#include <chrono>
#include <vector>
#include <memory>

class Player : public PhysicalEntity
{
public:
    Player(glm::vec3 position, FloatingPointType width, FloatingPointType height, FloatingPointType length, FloatingPointType translationSpeed, FloatingPointType rotationSpeed = 1.);
    void move(float dt, MovingDirection direction, std::vector<std::unique_ptr<PhysicalEntity>> const &collidingEntities);
    void rotate(float diffAngleX, float diffAngleZ);
    glm::mat4 createViewMatrix() const;

private:
    bool falling = true;
    void translate(MovingDirection direction, float dt);
    glm::mat4 createRotationMatrix() const;
    glm::mat4 createZRotationMatrix() const;
    float xAngle = glm::atan(glm::sqrt(8.f) / 2.f);
    float zAngle = glm::radians(180.f - 45.f);
    float translationSpeed;
    float rotationSpeed;
    glm::mat4 view;
};