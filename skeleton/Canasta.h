#pragma once
#include <PxPhysicsAPI.h>
#include "vector3D.h"
#include "RenderUtils.hpp"
#include <vector>

using namespace physx;

class Canasta {
public:
    Canasta(PxPhysics* physics, PxScene* scene, const Vector3D& pos, const Vector4& colorBoard = Vector4(1, 1, 1, 1), const Vector4& colorRim = Vector4(1, 0, 0, 1));
    ~Canasta();

    void setPosition(const Vector3D& p);
    Vector3D getPosition() const;

    void update(float dt);
    void render();
    PxRigidActor* getActor() const { return actor; }
    Vector3D getAro();
    float getAroRadius();

private:
    PxPhysics* physics = nullptr;
    PxScene* scene = nullptr;
    PxRigidStatic* actor = nullptr;

    std::vector<PxShape*> shapes;
    std::vector<RenderItem*> renders;
    PxVec3 initPos;
    std::vector<PxRigidStatic*> actors;
    std::vector<RenderItem*> renderItems;
};