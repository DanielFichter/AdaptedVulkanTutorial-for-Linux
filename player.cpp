#include "player.hpp"
#include "axes.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include <numbers>
#include <algorithm>

Player::Player(glm::vec3 position, FloatingPointType width, FloatingPointType length, FloatingPointType height, FloatingPointType translationSpeed, FloatingPointType rotationSpeed) : PhysicalEntity(position, width, length, height), translationSpeed{translationSpeed}, rotationSpeed{rotationSpeed}
{
}

void Player::move(float dt, MovingDirection direction, std::vector<std::unique_ptr<PhysicalEntity>> const &collidingEntities)
{
    translate(direction, dt);
    if (state == State::falling || state == State::walking)
    {
        fall(dt);
        if (detectCollision(collidingEntities))
        {
            if (verticalSpeed < 0)
            {
                while (detectCollision(collidingEntities))
                {
                    restoreFalling();
                    state = State::standing;
                    verticalSpeed = 0;
                }
            }
        }
        else if (state == State::walking)
        {
            state = State::falling;
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

void Player::jump()
{
    if (state != State::falling)
    {
        verticalSpeed = 1;
        state = State::falling;
    }
}

glm::mat4 Player::createViewMatrix() const
{
    const auto rotationMatrix = createRotationMatrix();
    return glm::translate(glm::transpose(rotationMatrix), -position);
}

bool Player::detectCollision(std::vector<std::unique_ptr<PhysicalEntity>> const & collidingEntities)
{
    return std::any_of(collidingEntities.begin(), collidingEntities.end(), [this] (const std::unique_ptr<PhysicalEntity>& pEntity) {
        return pEntity->collide(*this); });
}

void Player::translate(MovingDirection direction, float dt)
{
    if (direction != MovingDirection::none)
    {
        const auto directionVector = directionToAxis.at(direction);
        const auto zRotation = createZRotationMatrix();
        position += glm::vec3{zRotation * directionVector * translationSpeed * dt};
        if (state == State::standing)
        {
            state = State::walking;
        }
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