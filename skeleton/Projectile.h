#pragma once
#include "Particle.h"
#include "vector3D.h"
class Projectile : public Particle
{

private:
	float masaS;
	float masaR;
	Vector3D velR;
	Vector3D velS;

public:
	Projectile(Vector3D pos, Vector3D acel, float damping, float masaR, Vector3D velR, Vector3D velS );
	void integrate(double t) override;
};

