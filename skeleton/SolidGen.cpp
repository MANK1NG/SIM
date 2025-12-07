#include "SolidGen.h"
SolidGen::SolidGen(Vector3D origen_, float intervalo_, physx::PxMaterial* mat,
    physx::PxPhysics* physics_, physx::PxScene* scene_)
    : origen(origen_), intervalo(intervalo_), material(mat),
    physics(physics_), scene(scene_) {
}

SolidGen::~SolidGen()
{
    for (auto s : solidos) delete s;
}

void SolidGen::update(float dt)
{
    tiempo += dt;

    if (tiempo >= intervalo) {
        tiempo = 0;
        generateSolid();
    }
}

void SolidGen::generateSolid()
{
    physx::PxTransform pose(origen.getX(), origen.getY(),origen.getZ());
    physx::PxRigidDynamic* body = physics->createRigidDynamic(pose);

    physx::PxShape* shape = CreateShape(physx::PxBoxGeometry(1, 1, 1));
    shape->setMaterials(&material, 1);
    body->attachShape(*shape);

   physx::PxRigidBodyExt::updateMassAndInertia(*body, 100.0f);

    scene->addActor(*body);

    RenderItem* item = new RenderItem(shape, body, Vector4(0, 1, 0, 1));

    solidos.push_back(new Solid(body, item));
}