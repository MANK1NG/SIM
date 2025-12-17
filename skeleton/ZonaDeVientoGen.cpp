#include "ZonaDeVientoGen.h"
#include <iostream>

ZonaDeVientoGen::ZonaDeVientoGen(Vector3D v, float k1_, float k2_, Vector3D c, float r) : windVelocity(v), k1(k1_), k2(k2_), centro(c), radio(r)
{
}

void ZonaDeVientoGen::updateForce(physx::PxRigidDynamic* s, double t)
{
	
	physx::PxTransform pose = s->getGlobalPose();
	Vector3D pos(pose.p.x, pose.p.y, pose.p.z);

	Vector3D dist = pos - centro;
	float distM = dist.module();
	
	if (distM > radio) {
		
		return;
	}

	physx::PxVec3 v = s->getLinearVelocity();
	Vector3D velS(v.x, v.y, v.z);
	Vector3D diff = windVelocity - velS;
	float vel = diff.module();

	Vector3D fuerza = diff.multEscalar(k1) + diff.multEscalar(vel).multEscalar(k2);

	s->addForce(physx::PxVec3(fuerza.getX(),fuerza.getY(),fuerza.getZ()));
	}
