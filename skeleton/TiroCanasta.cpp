#include "tiroCanasta.h"
#include <iostream>

TiroCanasta::TiroCanasta(ForceSys* fs_):fuerza(0.0f), fuerzaMaxima(60.0f), masFuerza(10.0f), cargando(false), fs(fs_)
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
		fuerza += masFuerza*(t*15);
		if (fuerza > fuerzaMaxima) {
			fuerza = fuerzaMaxima;
		}
	}
}

void TiroCanasta::renderBarraCarga()
{
	if (cargando) {
		float porcentaje = fuerza / fuerzaMaxima;
		if (porcentaje > 1.0f) porcentaje = 1.0f;


		const float x = -0.8f, y = -0.8f;
		const float ancho = 0.6f, alto = 0.1f;
		const float anchoVerde = ancho * porcentaje;

		glPushAttrib(GL_ENABLE_BIT | GL_TRANSFORM_BIT);
		glDisable(GL_DEPTH_TEST);

		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		glOrtho(-1, 1, -1, 1, -1, 1);

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();

		// Fondo gris
		glColor3f(0.3f, 0.3f, 0.3f);
		glRectf(x, y, x + ancho, y + alto);

		// Barra verde
		glColor3f(0.0f, 1.0f, 0.0f);
		glRectf(x, y, x + anchoVerde, y + alto);

		glPopMatrix();
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glPopAttrib();
		glMatrixMode(GL_MODELVIEW);
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
	Projectile* p = new Projectile(spawnPos, Vector3D(0, 0, 0), 0.99f, 1.0f, Vector3D(8, 20, 0), vel);
	fs->addForce(p,gravityGen);
	bolas.push_back(p);

}
