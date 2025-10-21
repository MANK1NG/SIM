#pragma once
#include "vector3D.h"
#include "RenderUtils.hpp"
class Particle 
{
public:
	Particle(Vector3D Pos, Vector3D Vel, Vector3D Acc, float Dampling, float lifetime, Vector4 color, float tam);
	~Particle();

	virtual void integrate(double t);
	bool isAlive();
	physx::PxTransform pose;

protected:
	Vector3D vel;
	Vector3D acc;
	float damping;
	float lifeTime;
	float time;
	float tam;
	RenderItem* renderItem;
};

