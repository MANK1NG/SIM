#include "WindForceGen.h"

WindForceGen::WindForceGen( Vector3D v, float k1_, float k2_) : windVelocity(v), k1(k1_), k2(k2_)
{
}

void WindForceGen::updateForce(Particle* p, double t)
{

    Vector3D diff = windVelocity - p->getVel();

    float speed = diff.module();

    Vector3D force = diff.multEscalar(k1) + diff.multEscalar(speed).multEscalar(k2);

    p->addForce(force);
}
