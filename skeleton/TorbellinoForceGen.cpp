#include "TorbellinoForceGen.h"

TorbellinoForceGen::TorbellinoForceGen(const Vector3D& windVelocity_, float k1_, float k2_, Vector3D center_, float K_, float radius_) : WindForceGen(Vector3D(0, 0, 0), k1_, k2_), center(center_),K(K_), radius(radius_)
{
}

void TorbellinoForceGen::updateForce(Particle* p, double t)
{
    Vector3D pos = p->getPos();

    Vector3D dist(pos.getX() - center.getX(), 0.0f, pos.getZ() - center.getZ());
    float distM = dist.module();

    Vector3D tg(-dist.getZ(), 0.0f, dist.getX());
    tg = tg.multEscalar(1.0f / distM);

    
    float fz = K * (distM / radius);
    Vector3D fzv = tg.multEscalar(fz);

    Vector3D relVel = fzv - p->getVel();
    float speed = relVel.module();

    Vector3D force = relVel.multEscalar(k1) + relVel.multEscalar(speed * k2);
    p->addForce(force);
}
