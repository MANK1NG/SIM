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
	Projectile(Vector3D pos, float damping, float masaR, Vector3D velR, Vector3D velS, Vector4 color, float tam);
	//void integrate(double t) override;
};

