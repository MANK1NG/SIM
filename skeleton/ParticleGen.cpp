#include "ParticleGen.h"




ParticleGen::ParticleGen(Vector3D pos_, Vector3D vMed_, Vector3D vDevTip_, Vector3D gravity_, float damping_, float lifeTime_, float range_)
	:pos(pos_), vMed(vMed_),vDevTip(vDevTip_), gr(gravity_),damping(damping_), lifeTime(lifeTime_), range(range_), gen(std::random_device{}())
{
   

}

ParticleGen::~ParticleGen()
{
	for (Particle* p : particulas) {
		delete p;
	}

}

void ParticleGen::update(double dt)
{
	generateParticle();

    for (auto it = particulas.begin(); it != particulas.end();) {
        Particle* p = *it;
        if (p) {
            p->integrate(dt);

            if (!p->isAlive()) {
                delete p;
                it = particulas.erase(it);
                
            }
            Vector3D currentPos(p->pose.p.x, p->pose.p.y, p->pose.p.z);
            if ((currentPos - pos).module(currentPos - pos) > range) {
                delete p;
                it = particulas.erase(it);
                
            }
        }
        ++it;
    }
}

void ParticleGen::generateParticle()
{
	double vx = getRandomRange(vMed.getX(), vDevTip.getX());
	double vy= getRandomRange(vMed.getY(), vDevTip.getY());
	double vz = getRandomRange(vMed.getZ(), vDevTip.getZ());
	Vector3D vel(vx, vy, vz);
	
	particulas.push_back(new Particle(pos, vel, gr, damping, lifeTime));
}

int ParticleGen::getRandomRange(float min, float max) 
{

	 std::normal_distribution<float>dist(min, max);
     return dist(gen);
}