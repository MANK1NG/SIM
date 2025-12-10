#include "CanastaManager.h"
CanastaManager::CanastaManager(PxPhysics* physics_, PxScene* scene_):physics(physics_), scene(scene_) {}

CanastaManager::~CanastaManager()
{
    for (auto* b : baskets)
        delete b;
    baskets.clear();
}

void CanastaManager::addBasket( const Vector4& colorBoard, const Vector4& colorRim)
{
    float x = RandomFloat(-15.0, 15.0);
    float y = RandomFloat(10.0, 30.0);
    float z = -30;
    Vector3D pos = { x, y, z };
    Canasta* b = new Canasta(physics, scene, pos, colorBoard, colorRim);
    baskets.push_back(b);
    
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

float CanastaManager::RandomFloat(float min, float max)
{
    return min + (float) (rand()) / (float) (RAND_MAX / (max - min));
}
