#include "player.hpp"
#include "axes.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include <numbers>
#include <algorithm>

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
    if (std::any_of(collidingEntities.begin(), collidingEntities.end(), [this] (const std::unique_ptr<PhysicalEntity>& pEntity) {
        return pEntity->collide(*this); }))
    {
        falling = false;
        verticalSpeed = 0;
    }
    else if (!falling)
    {
        falling = true;
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

void Player::jump()
{
    if (!falling)
    {
        verticalSpeed = 1;
        falling = true;
    }
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