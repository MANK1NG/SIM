#include "Particle.h"

Particle::Particle(Vector3D Pos, Vector3D Vel, Vector3D Acc, float Dam, float lifeTime = 5.0f, Vector4 color= Vector4(0, 0, 1, 1), float tam = 2) : vel(Vel), acc(Acc), damping(Dam), lifeTime(lifeTime), time(0.0f), tam(tam)
{
	pose =  physx::PxTransform(physx::PxVec3(Pos.getX(), Pos.getY(), Pos.getZ()));
	
	renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(tam)), &pose, color);
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

	time += t;
}

bool Particle::isAlive()
{
	return time < lifeTime;
}
