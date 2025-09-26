#include "Particle.h"

Particle::Particle(Vector3D Pos, Vector3D Vel)
{

}

Particle::~Particle()
{
	DeregisterRenderItem(renderItem);
}

void Particle::integrate(double t)
{
	
}
