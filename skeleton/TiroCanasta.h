#pragma once
#include "Projectile.h"
#include "vector3D.h"
#include "core.hpp"
#include <vector>

class TiroCanasta
{
public:
	TiroCanasta();
	~TiroCanasta();
	void cargarDisparo();
	void soltarDisparo();
	void disparar();
	void update(double t);
private:
	float fuerza;
	float fuerzaMaxima = 60.0f;
	float masFuerza = 10.0f;
	bool cargando;
	std::vector<Projectile*> bolas;
	void crearBola(Vector3D pos, Vector3D dir, float fuerza);
};

