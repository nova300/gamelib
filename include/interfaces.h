#pragma once


namespace Collider2D
{

class Collider;
class CollisionInfo;
class ColliderSet;

class IHasCollider
{
public:
    virtual Collider GetCollider(ColliderSet* set = nullptr) = 0;
    virtual bool CheckColliderDirty(const Collider& other);
    virtual void OnCollision(const CollisionInfo& details) {};

};

};