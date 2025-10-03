#pragma once
#include "Particle.h"
#include "vector3D.h"
class Projectile : public Particle
{

private:
	float masaS;
	float masaR;
	float gr ;

public:
	Projectile(Vector3D pos, Vector3D vel, Vector3D acel, float damping, float masa, float gr);
	void integrate(double t) override;
};

