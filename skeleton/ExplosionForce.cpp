#include "ExplosionForce.h"

ExplosionForce::ExplosionForce(const Vector3D& c, float r, float K_, float t_) : center(c), radius(r), K(K_), t(t_), time(0.0f)
{
    activada = false;
}

void ExplosionForce::update(double dt)
{
    if(activada){
        time += dt;

    }
}

void ExplosionForce::updateForce(Particle* p, double dt)
{


    if (activada) {
        Vector3D dis = p->getPos() - center;
        float dist = dis.module();
        if (dist < radius) {
            float magnitude = K / (dist * dist) * physx::PxExp(-time / t);
            Vector3D force = dis.multEscalar(magnitude);
            p->addForce(force);

        }
    }
}

void ExplosionForce::explode()
{
    activada = true;
    time = 0.0;
}

