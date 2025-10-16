#pragma once
#include "ParticleGen.h"
#include <vector>
class ParticleSys
{
private:
	std::vector<ParticleGen*> particulasGen;
	~ParticleSys();
	void addParticle(ParticleGen* pg);
	void update(float dt);
};

