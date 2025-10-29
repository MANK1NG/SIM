#include "ParticleSys.h"
#include "ForceSys.h"

ParticleSys::ParticleSys(ForceSys* fs) : forceSys(fs)
{
}

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
	forceSys->update(dt);

	for (auto pg : particulasGen) {
		pg->update(dt);
	}
}
