#pragma once
#include "ForceGen.h"
#include "vector3D.h"
class WindForceGen :
    public ForceGen
{
public:
        
    WindForceGen(Vector3D v, float k1_, float k2_= 0.0f);

    void updateForce(Particle* p, double t) override;


protected:
    Vector3D windVelocity;
    float k1;
    float k2;
};

