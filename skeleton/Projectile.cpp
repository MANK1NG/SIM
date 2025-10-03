#include "Projectile.h"

Projectile::Projectile(Vector3D pos, Vector3D vel, Vector3D acel, float damping, float Masa, float Gr): Particle(pos, vel, acel, damping), masaR(Masa), gr(Gr)
{
	 
}

void Projectile::integrate(double t)
{
	
}


