#pragma once

#pragma once

#include "core/behaviour.h"
#include "physics/collider.h"
#include <raylib.h>


class Movement : public Behaviour
{
public:
    Movement(Object* obj);

    void SetMovementSpeed(float moveSpeed);
    void SetVelocity(Vector3 velocity);
    void SetVelocity(Vector2 velocity);
    void SetCollider(std::shared_ptr<Collider> collider);

    void Update(float deltaTime) override;

private:
    float moveSpeed = 1.0f;
    Vector3 velocity = Vector3Zero();
    std::shared_ptr<Collider> collider = nullptr;
};