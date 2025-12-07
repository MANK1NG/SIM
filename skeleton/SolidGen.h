#pragma once
#include <PxPhysicsAPI.h>
#include "vector3D.h"
#include "Solid.h"
#include <vector>

class SolidGen {
public:
    SolidGen(Vector3D origen, float intervalo, physx::PxMaterial* mat, physx::PxPhysics* physics, physx::PxScene* scene);
    ~SolidGen();

    void update(float dt);
    void generateSolid();

private:
    physx::PxPhysics* physics;
    physx::PxScene* scene;
    float tiempo = 0;
    float intervalo;
    Vector3D origen;
    physx::PxMaterial* material;
    std::vector<Solid*> solidos;
};