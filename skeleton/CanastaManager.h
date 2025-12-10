#pragma once
#include <list>
#include "Canasta.h"
#include "vector3D.h"
class CanastaManager{
public:
    CanastaManager(PxPhysics* physics, PxScene* scene);
    ~CanastaManager();

    void addBasket(const Vector4& colorBoard = Vector4(1, 1, 1, 1), const Vector4& colorRim = Vector4(1, 0, 0, 1));
    void removeBasket(Canasta* b);

    void clearB();

    void moveAll(const Vector3D& delta);

    void update(float dt);
    void render();
    float RandomFloat(float min, float max);
    const std::list<Canasta*>& getBaskets() const { return baskets; }

private:
    PxPhysics* physics = nullptr;
    PxScene* scene = nullptr;
    std::list<Canasta*> baskets;
    };