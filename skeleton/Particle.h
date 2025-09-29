#pragma once
#include "vector3D.h"
#include "RenderUtils.hpp"
class Particle 
{
public:
	Particle(Vector3D Pos, Vector3D Vel, Vector3D Acc);
	~Particle();

	void integrate(double t);
private:
	Vector3D vel;
	Vector3D acc;
	physx::PxTransform pose;
	RenderItem* renderItem;

};

