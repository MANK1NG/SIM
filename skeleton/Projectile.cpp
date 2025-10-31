#include "Projectile.h"


Projectile::Projectile(Vector3D pos,  Vector3D acel, float damping, float masaReal, Vector3D velReal, Vector3D velSimulada) : Particle(pos, velSimulada, damping, 10.0f,Vector4(0,0,0,1),1.0f, masaReal), masaR(masaReal), velR(velReal), velS(velSimulada)
{
	float modReal = velR.module();
	float modSim = velS.module();
	masaS = masaR * pow(modReal / modSim, 2);
	float factor = pow(modSim / modReal, 2);

	renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(2)), &pose, Vector4(1, 0.5, 0, 1));
	RegisterRenderItem(renderItem);
}



void Projectile::integrate(double t)
{
	Vector3D accForces = force.multEscalar(1.0f / mass);



	vel = vel + accForces.multEscalar(t);
	vel = vel.multEscalar(pow(damping, t));

	pose.p.x += vel.getX() * t;
	pose.p.y += vel.getY() * t;
	pose.p.z += vel.getZ() * t;
	clearForce();
}


