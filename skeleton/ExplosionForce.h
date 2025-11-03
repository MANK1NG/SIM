#pragma once
#include "ForceGen.h"
#include "vector3D.h"
class ExplosionForce :
    public ForceGen
{
public:
    ExplosionForce(const Vector3D& c, float r, float K_, float t_);
    void update(double dt) override;
    void updateForce(Particle* p, double t) override;
    void explode();
    void setCenter(Vector3D c) { center = c; };
private:
    Vector3D center;
    float radius;
    float K;
    float t;
    float time;
    bool activada;
};

