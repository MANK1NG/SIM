#pragma once
#include "Particle.h"
#include "vector3D.h"
#include "ForceGen.h"
#include "ForceSys.h"
#include <vector>
#include <random>

class ParticleGen
{
public:
	ParticleGen(Vector3D pos_,Vector3D vMed_, Vector3D vDevTip_, float damping_, float lifeTime_, float range_, float posRange_, Vector4 color, float tam_,float mass_, ForceSys* fs_);
	~ParticleGen();
	 void update(double dt) ;
	 void generateParticle() ;
	 void addForce(ForceGen* fg);

private:
	std::vector<Particle*> particulas;
	Vector3D pos;
	Vector3D vDevTip;
	Vector3D vMed;
	float damping;
	float lifeTime;
	float range;
	std::mt19937 gen;
	float posRange;
	Vector4 color;
	float tam;
	float mass;
	ForceSys* forceSys;
	std::vector<ForceGen*> forceGen;
	float getRandomRange(float a, float b) ;
};

