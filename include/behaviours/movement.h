#pragma once

#pragma once

#include "core/behaviour.h"
#include "physics/collider2d.h"
#include "interfaces.h"
#include <raylib.h>


class Movement : public Behaviour, public Collider2D::IHasCollider
{
public:
    ~Movement() {};

    void SetMovementSpeed(float moveSpeed);
    void SetVelocity(Vector3 velocity);
    void SetVelocity(Vector2 velocity);
    
    virtual Collider2D::Collider GetCollider(Collider2D::ColliderSet* set = nullptr) override;
    virtual void OnCollision(const Collider2D::CollisionInfo& details) override;

    Collider2D::Collider collider;
    void SetCollider(Collider2D::Collider COLLIDER);

    void Update(float deltaTime) override;
    void Init() override;

private:
    float moveSpeed = 1.0f;
    Vector3 velocity = Vector3Zero();
};