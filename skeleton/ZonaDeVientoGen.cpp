#include "ZonaDeVientoGen.h"
#include <iostream>

ZonaDeVientoGen::ZonaDeVientoGen(Vector3D v, float k1_, float k2_, Vector3D c, float r) : windVelocity(v), k1(k1_), k2(k2_), centro(c), radio(r)
{
}

void ZonaDeVientoGen::updateForce(Particle* p, double t)
{
	
	Vector3D dist = p->getPos() - centro;
	float distM = dist.module();
	
	if (distM > radio) {
		
		return;
	}

	Vector3D diff = windVelocity - p->getVel();
	float vel = diff.module();

	Vector3D fuerza = diff.multEscalar(k1) + diff.multEscalar(vel).multEscalar(k2);

	p->addForce(fuerza);
	}
