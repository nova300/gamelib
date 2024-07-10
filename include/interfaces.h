#pragma once


namespace Collider2D
{

class Collider;
class CollisionInfo;

class IHasCollider
{
public:
    virtual Collider GetCollider() = 0;
    virtual bool CheckColliderDirty(const Collider& other);
    virtual void OnCollision(const CollisionInfo& details) {};
};

};