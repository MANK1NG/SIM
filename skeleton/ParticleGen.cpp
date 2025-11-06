#include "ParticleGen.h"
#include <iostream>

ParticleGen::ParticleGen(Vector3D pos_, Vector3D vMed_, Vector3D vDevTip_, float damping_, float lifeTime_, float range_, float posRange_, Vector4 color_, float tam_,float mass_,  ForceSys* fs_, TDist TDist_)
	:pos(pos_), vMed(vMed_),vDevTip(vDevTip_),damping(damping_), lifeTime(lifeTime_), range(range_), posRange(posRange_),color(color_),tam(tam_),mass(mass_),forceSys(fs_),tDist(TDist_), gen(std::random_device{}())
{
    pausar = false;

}

ParticleGen::~ParticleGen()
{
	for (Particle* p : particulas) {
		delete p;
	}

}

void ParticleGen::update(double dt)
{
    tiempoEspera += dt;

    if (!pausar &&( tiempoMax < 0.0f || tiempoEspera < tiempoMax)) {
        generateParticle();

    }
    

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
    float px = getRandomRange(pos.getX() - posRange, pos.getX() + posRange);
    float py = getRandomRange(pos.getY() - posRange, pos.getY() + posRange);
    float pz = getRandomRange(pos.getZ() - posRange, pos.getZ() + posRange);
    Vector3D posRandom(px, py, pz);


    float vx = getRandomRange(vMed.getX() - vDevTip.getX(), vMed.getX() + vDevTip.getX());
    float vy = getRandomRange(vMed.getY() - vDevTip.getY(), vMed.getY() + vDevTip.getY());
    float vz = getRandomRange(vMed.getZ() - vDevTip.getZ(), vMed.getZ() + vDevTip.getZ());
	Vector3D vel(vx, vy, vz);
	
    Particle* p = new Particle(posRandom, vel, damping, lifeTime, color, tam, mass);
    particulas.push_back(p);
    
    if (forceSys) {
        for (auto fg : forceGen)
            forceSys->addForce(p, fg);
    }
}

float ParticleGen::getRandomRange(float a, float b) 
{
    if (tDist == TDist::NORMAL) {
        float media = (a + b) / 2.0f;
        float sigma = std::abs(b - a) / 6.0f;
        if (sigma == 0.0f) sigma = 0.0001f;
        std::normal_distribution<float>dist(media, sigma);
        return dist(gen);

    }else if(tDist == TDist::UNIFORME ) {
        std::uniform_real_distribution<float> dist(a, b);
        return dist(gen);
    }
    
   
}

void ParticleGen::addForce(ForceGen* fg){
    forceGen.push_back(fg);
}
