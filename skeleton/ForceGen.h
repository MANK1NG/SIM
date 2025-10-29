#pragma once
#include "Particle.h"


class ForceGen
{
public:
	virtual void updateForce(Particle* particle, double dt) = 0;
	virtual void update(double dt) {};
};

