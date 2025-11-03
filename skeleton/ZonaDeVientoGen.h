#pragma once
#include "ForceGen.h"
class ZonaDeVientoGen: public ForceGen
{
private:
	Vector3D windVelocity;
	float k1;
	float k2;
	Vector3D centro;
	float radio;
public:
	ZonaDeVientoGen(Vector3D v, float k1_, float k2_, Vector3D c, float r);
	virtual void updateForce(Particle* p, double t) override;
};

