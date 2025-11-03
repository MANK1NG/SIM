#pragma once
#include "vector3D.h"
#include "RenderUtils.hpp"
#include "ForceSys.h"
#include "PxRigidDynamic.h"

class Particle 
{
public:
	Particle(Vector3D Pos, Vector3D Vel, float Dampling, float lifetime, Vector4 color, float tam, float mass);
	~Particle();

	virtual void integrate(double t);
	bool isAlive() const;
	physx::PxTransform pose;
	float getMass() const { return mass; }
	void setMass(float m) { mass = m; }
	void addForce(const Vector3D f) { force = force + f; }
	void clearForce() { force = Vector3D(0, 0, 0); }
	Vector3D getVel()  { return vel; }
	Vector3D getPos();
protected:
	Vector3D pos;
	Vector3D vel;
	float damping;
	float lifeTime;
	float time;
	float tam;
	RenderItem* renderItem;
	float mass;
	Vector3D force;
	ForceSys* forceSys;
};

