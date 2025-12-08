#pragma once
#include "PxRigidDynamic.h"
#include "core.hpp"
#include <PxPhysicsAPI.h>
#include "RenderUtils.hpp"

class Solid {
public:
    Solid(physx::PxTransform t, physx::PxGeometry& geo, Vector3 linear_v, Vector3 ang_v, float masa, Vector4 color, physx::PxPhysics* phys, physx::PxScene* scene, physx::PxVec3 inertia);
       

    ~Solid();
    void setVelocity(Vector3 vel) { body->setLinearVelocity(vel); }
    bool isAlive() { return true; }
    physx::PxRigidDynamic* getBody() { return body; }
private:
    physx::PxRigidDynamic* body;
    physx::PxShape* shape;
    RenderItem* renderItem;
    physx::PxScene* gScene;

};