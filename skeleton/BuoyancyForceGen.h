#pragma once
#include "ForceGen.h"
class BuoyancyForceGen :
    public ForceGen
{
public:
    BuoyancyForceGen(float h, float V, float d, Particle* liquid);

    void updateForce(Particle* particle, double t)override;
    virtual ~BuoyancyForceGen();
protected:
    float _height;
    float _volume;
    float _liquid_density;
    float _gravity = 9.8;

    Particle* _liquid_particle;
};

