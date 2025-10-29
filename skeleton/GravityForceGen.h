#pragma once
#include "ForceGen.h"
class GravityForceGen : public ForceGen
{
private:
    Vector3D gravity;
public:
    GravityForceGen(Vector3D g);
    ~GravityForceGen() {};
    void updateForce(Particle* particle, double dt) override;
};

