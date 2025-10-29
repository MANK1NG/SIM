#include "Particle.h"

Particle::Particle(Vector3D pos_, Vector3D Vel, float Dam, float lifeTime = 5.0f, Vector4 color = Vector4(0, 0, 1, 1), float tam = 2, float mass_ = 1.0f) :pos(pos_), vel(Vel), damping(Dam), lifeTime(lifeTime), time(0.0f), tam(tam), mass(mass_)
{

	pose =  physx::PxTransform(physx::PxVec3(pos_.getX(), pos_.getY(), pos_.getZ()));
	
	renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(tam)), &pose, color);
	RegisterRenderItem(renderItem);
}

Particle::~Particle()
{
	DeregisterRenderItem(renderItem);
}

void Particle::integrate(double t)
{
	//Fuerzas
	Vector3D accForces = force.multEscalar(1.0f / mass);
	


	vel = vel + accForces.multEscalar(t) ;

	vel = vel.multEscalar(pow(damping, t));

	pose.p.x += vel.getX() * t;
	pose.p.y += vel.getY() * t;
	pose.p.z += vel.getZ() * t;

	clearForce();

	time += t;
}

bool Particle::isAlive() const
{
	return time < lifeTime;
}
