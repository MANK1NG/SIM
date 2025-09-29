#include "Particle.h"

Particle::Particle(Vector3D Pos, Vector3D Vel, Vector3D Acc) : vel(Vel), acc(Acc)
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
	vel = vel + acc * t;

	pose.p.x += vel.getX() * t;
	pose.p.y += vel.getY() * t;
	pose.p.z += vel.getZ() * t;
}
