#include "Canasta.h"
Canasta::Canasta(PxPhysics* physics_, PxScene* scene_, const Vector3D& pos, const Vector4& colorBoard, const Vector4& colorRim) : physics(physics_), scene(scene_)
{
    offsets = { { 5, -5, 6 },{ 0, -5, 11 },{ 0, -5, 1 },{ -5, -5, 6 },{ 0, 0, 0 }};
    PxMaterial* material = physics->createMaterial(0.5f, 0.5f, 0.5f);
    
    PxVec3 aux = { pos.getX(),pos.getY(),pos.getZ() };
    actors.clear();
    shapes.clear();
    renderItems.clear();
    actors.push_back(physics->createRigidStatic(PxTransform(PxVec3(offsets[0].getX(), offsets[0].getY(), offsets[0].getZ()) + aux)));
    PxShape* shape = actors[0]->createShape(PxBoxGeometry(0.5f, 1, 5), *material);
    scene->addActor(*actors[0]);

    renderItems.push_back(new RenderItem(shape, actors[0], colorRim));

    actors.push_back(physics->createRigidStatic(PxTransform(PxVec3(offsets[1].getX(), offsets[1].getY(), offsets[1].getZ()) + aux)));
    PxShape* shape2 = actors[1]->createShape(PxBoxGeometry(5, 1, 0.5f), *material);
    scene->addActor(*actors[1]);

    renderItems.push_back(new RenderItem(shape2, actors[1], colorRim));

    actors.push_back(physics->createRigidStatic(PxTransform(PxVec3(offsets[2].getX(), offsets[2].getY(), offsets[2].getZ()) + aux)));
    PxShape* shape3 = actors[2]->createShape(PxBoxGeometry(5, 1, 0.5f), *material);
    scene->addActor(*actors[2]);

    renderItems.push_back(new RenderItem(shape3, actors[2], colorRim));

    actors.push_back(physics->createRigidStatic(PxTransform(PxVec3(offsets[3].getX(), offsets[3].getY(), offsets[3].getZ()) + aux)));
    PxShape* shape4 = actors[3]->createShape(PxBoxGeometry(0.5f, 1, 5), *material);
    scene->addActor(*actors[3]);
    
    renderItems.push_back(new RenderItem(shape4, actors[3], colorRim));
    
    PxMaterial* materialBoard = physics->createMaterial(0.5f, 0.5f, 0.5f);
    actors.push_back(physics->createRigidStatic(PxTransform(PxVec3(offsets[4].getX(), offsets[4].getY(), offsets[4].getZ()) + aux)));
    PxShape* boardShape = actors[4]->createShape(PxBoxGeometry(10, 10, 0.5f), *materialBoard);
    scene->addActor(*actors[4]);

    renderItems.push_back(new RenderItem(boardShape, actors[4], colorBoard));
    volante = new Particle( pos,Vector3D(0, 0, 0),0.98f,99999.0f, Vector4(0, 0, 0, 0),0.1f,1.0f);
}

Canasta::~Canasta()
{
    delete volante;
    for (auto* r : renderItems) {
        if (r) DeregisterRenderItem(r);
    }
    renderItems.clear();

    for (size_t i = 0; i < shapes.size() && i < actors.size(); ++i) {
        PxShape* s = shapes[i];
        if (s) {
            if (actors[i]) {
                
                actors[i]->detachShape(*s);
               
            }
            s->release();
        }
    }
    shapes.clear();

    for (auto* a : actors) {
        if (!a) continue;
         scene->removeActor(*a);
        a->release();
    }
    actors.clear();
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
    if (!volante) return;
    volante->integrate(dt);
    Vector3D basePos = volante->getPos();

    for (int i= 0; i< actors.size(); i++)
    {
        PxTransform t =actors[i]->getGlobalPose();
        t.p = PxVec3(basePos.getX() + offsets[i].getX(), basePos.getY() + offsets[i].getY(), basePos.getZ()+ offsets[i].getZ());
        actors[i]->setGlobalPose(t);
    }
}

void Canasta::render()
{
  
}

Vector3D Canasta::getAro()
{
    PxVec3 posDer = actors[0]->getGlobalPose().p;
    PxVec3 posIzq = actors[3]->getGlobalPose().p;
    float centroX = (posDer.x + posIzq.x) / 2.0f;
    float centroY = posDer.y;
    float centroZ = posDer.z;
    return Vector3D(centroX, centroY, centroZ);
}

float Canasta::getAroRadius()
{
    return 4.0f;
}


