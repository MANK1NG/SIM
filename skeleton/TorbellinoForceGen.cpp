#include "TorbellinoForceGen.h"

TorbellinoForceGen::TorbellinoForceGen(const Vector3D& windVelocity_, float k1_, float k2_, Vector3D center_, float K_, float radius_) : WindForceGen(Vector3D(0, 0, 0), k1_, k2_), center(center_),K(K_), radius(radius_)
{
}

void TorbellinoForceGen::updateForce(Particle* p, double t)
{
    Vector3D pos = p->getPos();
    Vector3D diff = pos - center;

  
    Vector3D aux = { -K*(pos.getZ() - center.getZ()), 0,K*( pos.getX() - center.getX())};

    Vector3D relativeVel = windVelocity - p->getVel();
    float speed = relativeVel.module();

    Vector3D force = relativeVel.multEscalar(k1)
        + relativeVel.multEscalar(speed * k2);

    p->addForce(force);
}
