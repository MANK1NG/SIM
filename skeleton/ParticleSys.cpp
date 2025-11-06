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

	for (auto it = particulasGen.begin(); it != particulasGen.end(); )
	{
		ParticleGen* pg = *it;
		
			pg->update(dt);

		
		if (pg->isAlive() && pg->isEmpty())
		{
			delete pg;
			it = particulasGen.erase(it);
		}
		else
		{
			++it;
		}
	}
}
