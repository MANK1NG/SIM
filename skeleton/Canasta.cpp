#include "Canasta.h"
Canasta::Canasta(PxPhysics* physics_, PxScene* scene_, const Vector3D& pos, const Vector4& colorBoard, const Vector4& colorRim) : physics(physics_), scene(scene_)
{
    PxMaterial* material = physics->createMaterial(0.5f, 0.5f, 0.5f);
    PxVec3 aux = { pos.getX(),pos.getY(),pos.getZ() };
    actors.push_back(physics->createRigidStatic(PxTransform(PxVec3(5, -5, 6) + aux)));
    PxShape* shape = actors[0]->createShape(PxBoxGeometry(0.5f, 1, 5), *material);
    scene->addActor(*actors[0]);

    renderItems.push_back(new RenderItem(shape, actors[0], colorRim));

    actors.push_back(physics->createRigidStatic(PxTransform(PxVec3(0, -5, 11) + aux)));
    PxShape* shape2 = actors[1]->createShape(PxBoxGeometry(5, 1, 0.5f), *material);
    scene->addActor(*actors[1]);

    renderItems.push_back(new RenderItem(shape2, actors[1], colorRim));

    actors.push_back(physics->createRigidStatic(PxTransform(PxVec3(0, -5, 1) + aux)));
    PxShape* shape3 = actors[2]->createShape(PxBoxGeometry(5, 1, 0.5f), *material);
    scene->addActor(*actors[2]);

    renderItems.push_back(new RenderItem(shape3, actors[2], colorRim));

    actors.push_back(physics->createRigidStatic(PxTransform(PxVec3(-5, -5, 6) + aux)));
    PxShape* shape4 = actors[3]->createShape(PxBoxGeometry(0.5f, 1, 5), *material);
    scene->addActor(*actors[3]);
    
    renderItems.push_back(new RenderItem(shape4, actors[3], colorRim));
    
    PxMaterial* materialBoard = physics->createMaterial(0.5f, 0.5f, 0.5f);
    actors.push_back(physics->createRigidStatic(PxTransform(PxVec3(0, 0, 0) + aux)));
    PxShape* boardShape = actors[4]->createShape(PxBoxGeometry(10, 10, 0.5f), *materialBoard);
    scene->addActor(*actors[4]);

    renderItems.push_back(new RenderItem(boardShape, actors[4], colorBoard));

}

Canasta::~Canasta()
{
    for (auto r : renders) {
        if (r) DeregisterRenderItem(r);
    }
    renders.clear();
    for (auto s : shapes) {
        actor->detachShape(*s);

    }
    scene->removeActor(*actor);
    actor->release();
    for (auto s : shapes) {
        s->release();
    }
    shapes.clear();
}

void Canasta::setPosition(const Vector3D& pos)
{
    if (!actor) return;
    PxTransform t = actor->getGlobalPose();
    t.p = { pos.getX(),pos.getY(),pos.getZ() };
    actor->setGlobalPose(t);
}

Vector3D Canasta::getPosition() const
{
    if (!actor) {
        return Vector3D({ 0,0,0 });
    }
    Vector3D aux = { actor->getGlobalPose().p.x,actor->getGlobalPose().p.y,actor->getGlobalPose().p.z };
    return aux;
}

void Canasta::update(float dt)
{
}

void Canasta::render()
{

}

Vector3D Canasta::getAro()
{
    PxVec3 pos = actors[0]->getGlobalPose().p;

    return Vector3D(pos.x, pos.y + 1.0f, pos.z);
}

float Canasta::getAroRadius()
{
    return 5.0f;
}


