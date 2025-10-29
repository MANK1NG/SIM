#pragma once
#include "ParticleGen.h"
#include "ForceSys.h"
#include <vector>
class ParticleSys
{
private:
	std::vector<ParticleGen*> particulasGen;
	ForceSys* forceSys;
public:
	ParticleSys(ForceSys* fs);
	~ParticleSys();
	void addParticle(ParticleGen* pg);
	void update(float dt);
};

