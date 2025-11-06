#include "tiroCanasta.h"
#include <iostream>
TiroCanasta::TiroCanasta(ForceSys* fs_, ParticleSys* ps_):fuerza(0.0f), fuerzaMaxima(60.0f), masFuerza(10.0f), cargando(false), fs(fs_), ps(ps_)
{


	tipoBolaN = 1;

	//Zona Viento
	Vector3D viento(10.0f, 0.0f, 0.0f);
	Vector3D zona(0.0f, 5.0f, -11.5f);
	float radio = 5.0f;
	poseZonaViento = physx::PxTransform(physx::PxVec3(zona.getX(), zona.getY(), zona.getZ()));
	zonaViento = new ZonaDeVientoGen(viento, 0.2f, 0.05f, zona, radio);
	rZonaViento = new RenderItem(CreateShape(physx::PxSphereGeometry(radio)), &poseZonaViento,Vector4(0.2f, 0.5f, 1.0f, 0.3f));

	//Explosion
	explosionBol = new ExplosionForce(Vector3D(0, 0, 0), 15.0f, 150000.0f, 1.0f);
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
	
	disparar();
}
void TiroCanasta::update(double t) {
	for (auto it = bolas.begin(); it != bolas.end();) {
		Projectile* p = *it;
		p->integrate(t);
		if (!p->isAlive()) {
			delete p;
			it = bolas.erase(it);
		}
		else {
			++it;
		}
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
		if (porcentaje > 1.0f) {
			porcentaje = 1.0f;
		}


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

void TiroCanasta::cambiarBola(int cb) 
{
	tipoBolaN = cb;
}

void TiroCanasta::activarExplosion()
{
	if (bolas.empty()) {
		return;
	}


	Projectile* ultBol = bolas.back();
	Vector3D posBol = ultBol->getPos();

	explosionBol->setCenter(posBol);
	explosionBol->explode();

	

	ParticleGen* gen = new ParticleGen(posBol,Vector3D(0.0f, 0.0f, 0.0f), Vector3D(10.0f, 10.0f, 10.0f)
		,0.95f,2.0f,8.0f,0.5f,Vector4(1.0f, 0.6f, 0.2f, 1.0f),0.2f,0.5f,fs, TDist::UNIFORME);

	gen->setTiempoMax(0.3f);
	explosionBol->activada = false;


	ps->addParticle(gen);
	fs->removeForces(ultBol);
	delete ultBol;
	bolas.pop_back();
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
	if (tipoBolaN == 3) {
		tp.masa = 0.5f;
		tp.color = Vector4(0.4f, 0.7f, 1.0f, 1.0f);
		tp.tam = 0.1f;
		tp.velReal =  Vector3D(10, 25, 0);
	}
	else if (tipoBolaN == 2) {
		tp.masa = 5.0f;
		tp.color = Vector4(0.5f, 0.5f, 0.5f, 1.0f);
		tp.tam = 5.0f;
		tp.velReal = Vector3D(4, 10, 0);
	}
	else {
		tp.masa = 1.0f;
		tp.color = Vector4(1.0f, 0.7f, 0.2f, 1.0f);
		tp.tam = 1.0f;
		tp.velReal = Vector3D(8, 20, 0);
	}
	Vector3D spawnPos = pos + dir.multEscalar(3.0f);
	Vector3D vel = dir.multEscalar(fuerza);
	
	Projectile* p = new Projectile(spawnPos, 0.99f, tp.masa, tp.velReal, vel, tp.color,tp.tam);
	fs->addForce(p,gravityGen);
	fs->addForce(p, zonaViento);
	fs->addForce(p, explosionBol);
	bolas.push_back(p);

}
