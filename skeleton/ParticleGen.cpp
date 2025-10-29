#include "ParticleGen.h"

ParticleGen::ParticleGen(Vector3D pos_, Vector3D vMed_, Vector3D vDevTip_, float damping_, float lifeTime_, float range_, float posRange_, Vector4 color_, float tam_,float mass_,  ForceSys* fs_)
	:pos(pos_), vMed(vMed_),vDevTip(vDevTip_),damping(damping_), lifeTime(lifeTime_), range(range_), posRange(posRange_),color(color_),tam(tam_),mass(mass_),forceSys(fs_), gen(std::random_device{}())
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
        
            p->integrate(dt);
            
           
            Vector3D currentPos(p->pose.p.x, p->pose.p.y, p->pose.p.z);
            Vector3D delta = currentPos - pos;
            float dist = sqrt(delta.getX() * delta.getX() + delta.getY() * delta.getY() +delta.getZ() * delta.getZ());

            if (!p->isAlive() || dist > range) {
                delete p;
                it = particulas.erase(it);
            }
            else {
                ++it;
            }
    }
}

void ParticleGen::generateParticle()
{
    float px = getRandomRange((float)pos.getX(), (float)posRange);
    float py = getRandomRange((float)pos.getY(), (float)posRange);
    float pz = getRandomRange((float)pos.getZ(), (float)posRange);
    Vector3D posRandom(px, py, pz);


	double vx = getRandomRange(vMed.getX(), vDevTip.getX());
	double vy= getRandomRange(vMed.getY(), vDevTip.getY());
	double vz = getRandomRange(vMed.getZ(), vDevTip.getZ());
	Vector3D vel(vx, vy, vz);
	
    Particle* p = new Particle(posRandom, vel, damping, lifeTime, color, tam, mass);
    particulas.push_back(p);
    
    if (forceSys) {
        for (auto fg : forceGen)
            forceSys->addForce(p, fg);
    }
}

int ParticleGen::getRandomRange(float min, float max) 
{

	 std::normal_distribution<float>dist(min, max);
     return dist(gen);
}

void ParticleGen::addForce(ForceGen* fg){
    forceGen.push_back(fg);
}
