#include "Particle.h"

Particle::Particle(Vector3D Pos, Vector3D Vel, Vector3D Acc, float Dam, float lifeTime = 5.0f) : vel(Vel), acc(Acc), damping(Dam), lifeTime(lifeTime), time(0.0f)
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

bool Particle::isAlive()
{
	return time < lifeTime;
}
