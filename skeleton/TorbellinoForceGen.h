#pragma once
#include "WindForceGen.h"
#include "Vector3D.h"
#include "Particle.h"
class TorbellinoForceGen :
    public WindForceGen
{
private:
    Vector3D center;  
    float K;         
    float radius;    

public:
    TorbellinoForceGen(const Vector3D& windVelocity, float k1, float k2,Vector3D center, float K_, float radius_);

    void updateForce(Particle* p, double t) override;
};


