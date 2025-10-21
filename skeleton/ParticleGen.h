#pragma once
#include "Particle.h"
#include "vector3D.h"
#include <vector>
#include <random>

class ParticleGen
{
public:
	ParticleGen(Vector3D pos_,Vector3D vMed_, Vector3D vDevTip_, Vector3D gravity_ , float damping_, float lifeTime_, float range_, float posRange_, Vector4 color, float tam_);
	~ParticleGen();
	 void update(double dt) ;
	 void generateParticle() ;
private:
	std::vector<Particle*> particulas;
	Vector3D pos;
	Vector3D vDevTip;
	Vector3D vMed;
	Vector3D gr;
	float damping;
	float lifeTime;
	float range;
	std::mt19937 gen;
	float posRange;
	Vector4 color;
	float tam;

	int getRandomRange(float min, float max) ;

};

