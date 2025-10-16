#include "ParticleSys.h"

ParticleSys::~ParticleSys()
{
	for (auto pg : particulasGen) {
		delete pg;
	}
}

void ParticleSys::addParticle(ParticleGen* pg)
{
	particulasGen.push_back(pg);
}

void ParticleSys::update(float dt)
{
	for (auto pg : particulasGen) {
		pg->update(dt);
	}
}
