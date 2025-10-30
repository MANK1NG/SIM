#include "tiroCanasta.h"
#include <iostream>

TiroCanasta::TiroCanasta():fuerza(0.0f), fuerzaMaxima(60.0f), masFuerza(10.0f), cargando(false)
{
	
}

TiroCanasta::~TiroCanasta()
{
	for (auto b : bolas) {
		delete b;
	}
}

void TiroCanasta::cargarDisparo()
{
	if (!cargando){
		cargando = true;
		fuerza = 0.0f;
	}
	
}
void TiroCanasta::soltarDisparo()
{
	cargando = false;
	
	physx::PxVec3 eye = GetCamera()->getEye();
	physx::PxVec3 dir = GetCamera()->getDir();
	Vector3D pos(eye.x, eye.y, eye.z);
	Vector3D dirVec(dir.x, dir.y, dir.z);
	dirVec.normalice();

	crearBola(pos, dirVec, fuerza);

	fuerza = 0.0f;
}
void TiroCanasta::update(double t) {
	for (auto b : bolas) {
		b->integrate(t);
	}
	if (cargando) {
		fuerza += masFuerza * t;
		if (fuerza > fuerzaMaxima) {
			fuerza = fuerzaMaxima;
		}
	}
}

void TiroCanasta::disparar()
{
	physx::PxVec3 eye = GetCamera()->getEye();
	physx::PxVec3 dir = GetCamera()->getDir();

	Vector3D pos(eye.x, eye.y, eye.z);
	Vector3D dirVec(dir.x, dir.y, dir.z);
	dirVec.normalice();

	crearBola(pos, dirVec, fuerza);
	fuerza = 0.0f;
}

void TiroCanasta::crearBola(Vector3D pos, Vector3D dir, float fuerza)
{
	
	Vector3D spawnPos = pos + dir.multEscalar(3.0f);
	Vector3D vel = dir.multEscalar(fuerza);
	Projectile* p = new Projectile(spawnPos, Vector3D(0, 0, 0), 0.99f, 1.0f, Vector3D(8, 20, 0), vel, Vector3D(0, -9.8f, 0));
	bolas.push_back(p);

}
