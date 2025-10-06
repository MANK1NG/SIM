#include "Projectile.h"


Projectile::Projectile(Vector3D pos,  Vector3D acel, float damping, float masaReal, Vector3D velReal, Vector3D velSimulada, Vector3D grReal) : Particle(pos, velSimulada, acel, damping), masaR(masaReal), velR(velReal), velS(velSimulada),grR(grReal)
{
	float modReal = velR.module(velR);
	float modSim = velS.module(velS);
	masaS = masaR * pow(modReal / modSim, 2);
	float factor = pow(modSim / modReal, 2);
	grS = Vector3D(grR.getX() * factor, grR.getY() * factor, grR.getZ() * factor);

	renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(2)), &pose, Vector4(1, 0.5, 0, 1));
	RegisterRenderItem(renderItem);
}



void Projectile::integrate(double t)
{
	acc = grS;


	vel = vel + acc.multEscalar(t);
	vel = vel.multEscalar(pow(damping, t));

	pose.p.x += vel.getX() * t;
	pose.p.y += vel.getY() * t;
	pose.p.z += vel.getZ() * t;
}


