#include "GravityForceGen.h"

GravityForceGen::GravityForceGen(Vector3D g) : gravity(g)
{
}

void GravityForceGen::updateForce(Particle* particle, double dt)
{
  
    Vector3D force = gravity.multEscalar(particle->getMass());
    particle->addForce(force);
}
