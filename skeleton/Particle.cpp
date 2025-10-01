#include "Particle.h"

Particle::Particle(Vector3D Pos, Vector3D Vel, Vector3D Acc, float Dam) : vel(Vel), acc(Acc), damping(Dam)
{
	pose =  physx::PxTransform(physx::PxVec3(Pos.getX(), Pos.getY(), Pos.getZ()));
	renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(2)), &pose, Vector4(0, 1, 0, 1));
	RegisterRenderItem(renderItem);
}

Particle::~Particle()
{
	DeregisterRenderItem(renderItem);
}

void Particle::integrate(double t)
{
	vel = vel + acc.multEscalar(t) ;

	vel = vel.multEscalar( pow(damping, t));

	pose.p.x += vel.getX() * t;
	pose.p.y += vel.getY() * t;
	pose.p.z += vel.getZ() * t;
}
