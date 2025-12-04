#include "SpringForceGen.h"

SpringForceGenerator::SpringForceGenerator(double k, double resting_length, Particle* other)
{
    _k = k;
    _resting_length = resting_length;
    _other = other;
}

void SpringForceGenerator::updateForce(Particle* particle,double t)
{
    Vector3D relative_pos_vector = _other->getPos() - particle->getPos();
    Vector3D force;

    const float length = relative_pos_vector.module();
    const Vector3D dir = relative_pos_vector.normalice();
    const float delta_x = length - _resting_length;
    Vector3D tramite= dir.multEscalar(_k);

    force = tramite.multEscalar(_k);
    particle->addForce(force);
}
