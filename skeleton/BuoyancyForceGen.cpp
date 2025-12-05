#include "BuoyancyForceGen.h"

BuoyancyForceGen::BuoyancyForceGen(float h, float V, float d)
{
}

void BuoyancyForceGen::updateForce(Particle* particle, double t)
{
	float h = particle->getPos().getY();
	float h0 = _liquid_particle->getPos().getY();

	Vector3D f(0, 0, 0);
	float immersed = 0.0;
	if (h - h0 > _height * 0.5) {
		immersed = 0.0;
	}
	else if (h0 - h > _height * 0.5) {
		immersed = 1.0;
	}
	else {
		immersed = (h0 - h) / _height + 0.5;
	}
	f.setY(_liquid_density * _volume * immersed * 9.8);
	particle->addForce(f);
}

BuoyancyForceGen::~BuoyancyForceGen()
{
}
