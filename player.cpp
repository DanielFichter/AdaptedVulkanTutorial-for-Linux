#include "player.hpp"
#include "axes.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include <numbers>

Player::Player(glm::vec3 position, FloatingPointType width, FloatingPointType height, FloatingPointType length, FloatingPointType translationSpeed, FloatingPointType rotationSpeed) : PhysicalEntity(position, width, height, length), translationSpeed{translationSpeed}, rotationSpeed{rotationSpeed}
{
}

void Player::move(float dt, MovingDirection direction, std::vector<std::unique_ptr<PhysicalEntity>> const &collidingEntities)
{
    translate(direction, dt);
    if (falling)
    {
        fall(dt);
    }
    for (auto const &entity : collidingEntities)
    {
        if (entity->collide(*this))
        {
            falling = false;
        }
    }
}

void Player::rotate(float diffAngleX, float diffAngleZ)
{
    if (const auto newXAngle = xAngle - diffAngleX * rotationSpeed;
        newXAngle >= 0 && newXAngle <= std::numbers::pi_v<float>)
    {
        xAngle = newXAngle;
    }

    zAngle -= diffAngleZ * rotationSpeed;
}

glm::mat4 Player::createViewMatrix() const
{
    const auto rotationMatrix = createRotationMatrix();
    return glm::translate(glm::transpose(rotationMatrix), -position);
}

void Player::translate(MovingDirection direction, float dt)
{
    if (direction != MovingDirection::none)
    {
        const auto directionVector = directionToAxis.at(direction);
        const auto zRotation = createZRotationMatrix();
        position += glm::vec3{zRotation * directionVector * translationSpeed * dt};
    }
}

glm::mat4 Player::createRotationMatrix() const
{
    const auto zRotation = createZRotationMatrix();
    return glm::rotate(zRotation, xAngle, glm::vec3{Axes::x});
}

glm::mat4 Player::createZRotationMatrix() const
{
    return glm::rotate(glm::mat4{1.f}, zAngle, glm::vec3{Axes::z});
}