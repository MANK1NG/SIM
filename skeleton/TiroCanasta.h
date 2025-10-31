#pragma once
#include "Projectile.h"
#include "vector3D.h"
#include "GravityForceGen.h"
#include "ForceSys.h"
#include "core.hpp"
#include <vector>

class TiroCanasta
{
public:
	TiroCanasta(ForceSys* fs_);
	~TiroCanasta();
	void cargarDisparo();
	void soltarDisparo();
	void disparar();
	void update(double t);
	void renderBarraCarga();
private:
	float fuerza;
	float fuerzaMaxima = 60.0f;
	float masFuerza = 5.0f;
	bool cargando;
	ForceSys* fs;
	GravityForceGen* gravityGen = new GravityForceGen(Vector3D(0, -10, 0));
	std::vector<Projectile*> bolas;
	void crearBola(Vector3D pos, Vector3D dir, float fuerza);
};

