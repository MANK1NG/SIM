#pragma once
#include "Projectile.h"
#include "vector3D.h"
#include "GravityForceGen.h"
#include "ZonaDeVientoGen.h"
#include "ExplosionForce.h"
#include "ForceSys.h"
#include "core.hpp"
#include <vector>
#include "ParticleGen.h"
#include "ParticleSys.h"

class TiroCanasta
{
public:
	TiroCanasta(ForceSys* fs_, ParticleSys* ps_);
	~TiroCanasta();
	void cargarDisparo();
	void soltarDisparo();
	void disparar();
	void update(double t);
	void renderBarraCarga();
	void cambiarBola(int cb);
	void activarExplosion();

private:
	struct tipoBola {
		float masa;
		Vector4 color;
		float tam;
		Vector3D velReal;
	};
	float fuerza;
	float fuerzaMaxima = 60.0f;
	float masFuerza = 5.0f;
	bool cargando;
	ForceSys* fs;
	ParticleSys* ps;
	int tipoBolaN;
	float masa;
	tipoBola tp;

	GravityForceGen* gravityGen = new GravityForceGen(Vector3D(0, -10, 0));
	ExplosionForce* explosionBol;
	std::vector<Projectile*> bolas;
	std::vector<ParticleGen*> generadoresBolas;
	ZonaDeVientoGen* zonaViento;
	RenderItem* rZonaViento;
	physx::PxTransform poseZonaViento;

	void crearBola(Vector3D pos, Vector3D dir, float fuerza);

};

