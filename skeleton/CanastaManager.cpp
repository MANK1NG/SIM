#include "CanastaManager.h"
CanastaManager::CanastaManager(PxPhysics* physics_, PxScene* scene_):physics(physics_), scene(scene_) {}

CanastaManager::~CanastaManager()
{
    for (auto* b : baskets)
        delete b;
    baskets.clear();
}

Canasta* CanastaManager::addBasket(const Vector3D& pos, const Vector4& colorBoard, const Vector4& colorRim)
{
    Canasta* b = new Canasta(physics, scene, pos, colorBoard, colorRim);
    baskets.push_back(b);
    return b;
}

void CanastaManager::removeBasket(Canasta* b)
{
    baskets.remove(b);
    delete b;
}

void CanastaManager::clearB()
{
    for (auto b : baskets) {
        delete b;
    }
    baskets.clear();
}

void CanastaManager::moveAll(const Vector3D& delta)
{
    for (auto* b : baskets) {
        Vector3D newPos = b->getPosition() + delta;
        b->setPosition(newPos);
    }
}

void CanastaManager::update(float dt)
{
    for (auto* b : baskets) {
        b->update(dt);
    }
}

void CanastaManager::render()
{
    for (auto* b : baskets)
        b->render();
}