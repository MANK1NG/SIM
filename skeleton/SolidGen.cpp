#include "SolidGen.h"
SolidGen::SolidGen(Vector3D origen_, Vector3D velInicial_, float intervalo_, physx::PxMaterial* mat,
    physx::PxPhysics* physics_, physx::PxScene* scene_)
    : origen(origen_), vel(velInicial_), intervalo(intervalo_), material(mat),
    physics(physics_), scene(scene_) {
    active = true;
}

SolidGen::~SolidGen()
{
    for (auto s : solidos) delete s;
}

void SolidGen::update(float dt)
{
    if (!active) {
        return;
    }
    tiempo += dt;

    if (tiempo >= intervalo) {
        tiempo = 0;
        generateSolid();
    }
    for (auto it = solidos.begin(); it != solidos.end(); ) {
        (*it)->update(dt);
        if (!(*it)->isAlive()) {
            delete* it;
            it = solidos.erase(it);
        }
        else {
            ++it;
        }
    }
}

void SolidGen::generateSolid()
{
    float yOffset = ((rand() % 100) / 100.0f - 0.5f) * 2.0f;

    physx::PxTransform pose(origen.getX(), origen.getY(),origen.getZ());

    physx::PxBoxGeometry shape = physx::PxBoxGeometry(1.2f, 1.2f, 1.2f);
    Vector3 angVel(0.0f,10.0f, 0.0f);
    Solid* s = new Solid(pose,shape,Vector3(vel.getX(), vel.getY(), vel.getZ()),angVel,1.0f,Vector4(0.05f, 0.05f, 0.05f, 1),physics,scene,physx::PxVec3(1, 1, 1),4.0f);
    solidos.push_back(s);
}
bool SolidGen::isActive(){
    return active;
}