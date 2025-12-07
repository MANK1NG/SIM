#pragma once
#include "PxPhysicsAPI.h"
#include "RenderUtils.hpp"

class Solid {
public:
    Solid(physx::PxRigidDynamic* body, RenderItem* item)
        : body(body), renderItem(item) {
    }

    ~Solid() {
        DeregisterRenderItem(renderItem);
        body->release();
    }

    bool isAlive() { return true; }

private:
    physx::PxRigidDynamic* body;
    RenderItem* renderItem;
};