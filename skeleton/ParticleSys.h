#pragma once
#include "ParticleGen.h"
#include <vector>
class ParticleSys
{
public:
	std::vector<ParticleGen*> particulasGen;
	~ParticleSys();
	void addParticle(ParticleGen* pg);
	void update(float dt);
};

