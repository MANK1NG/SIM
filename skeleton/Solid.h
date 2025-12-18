#pragma once
#include "PxRigidDynamic.h"
#include "core.hpp"
#include <PxPhysicsAPI.h>
#include "RenderUtils.hpp"

class Solid {
public:
    Solid(physx::PxTransform t, physx::PxGeometry& geo, Vector3 linear_v, Vector3 ang_v, float masa, Vector4 color, physx::PxPhysics* phys, physx::PxScene* scene, physx::PxVec3 inertia, float lifeTime_ = 5.0f);
       

    ~Solid();
    void setVelocity(Vector3 vel) { body->setLinearVelocity(vel); }
    bool isAlive() { return alive; }
    physx::PxRigidDynamic* getBody() { return body; }
    void update(double dt);

private:
    physx::PxRigidDynamic* body;
    physx::PxShape* shape;
    RenderItem* renderItem;
    physx::PxScene* gScene;
    float lifeTime;
    float timeAlive = 0.0f;
    bool alive = true;
};