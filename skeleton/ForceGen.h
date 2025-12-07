#pragma once
#include "Particle.h"


class ForceGen
{
protected:
	bool activo = true;
public:
	virtual void updateForce(Particle* particle, double dt) = 0;
	virtual void update(double dt) {};
	virtual physx::PxVec3 getForce(physx::PxRigidDynamic* solid) {
		return physx::PxVec3(0, 0, 0);
	}
	void toggleActivo() { activo = !activo; }
	bool getActivo() const { return activo; }

};

