#include "Projectile.h"
#include <iostream>


Projectile::Projectile(Vector3D pos, float damping, float masaReal, Vector3D velReal, Vector3D velSimulada, Vector4 color, float tam)
    : Particle(pos, velSimulada, damping, 5.0f, color, tam, masaReal),masaR(masaReal), velR(velReal), velS(velSimulada)
{
    float modSim = velSimulada.module();
	if (modSim < 0.001f) {
		modSim = 0.001f;
	}  

    masaS = masaR * pow(velReal.module() / modSim, 2);

    if (masaS < 0.01f) masaS = 0.01f;

    mass = masaS;
}
