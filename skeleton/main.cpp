#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>
#include "vector3D.h"
#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"
#include "Particle.h"
#include "Projectile.h"

#include <iostream>
#include "ParticleGen.h"
#include "ParticleSys.h"
#include "GravityForceGen.h"
#include "WindForceGen.h"
#include "TorbellinoForceGen.h"
#include "ExplosionForce.h"
#include "TiroCanasta.h"
std::string display_text = "This is a test";


using namespace physx;

PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;

PxFoundation*			gFoundation = NULL;
PxPhysics*				gPhysics	= NULL;


PxMaterial*				gMaterial	= NULL;

PxPvd*                  gPvd        = NULL;

PxDefaultCpuDispatcher*	gDispatcher = NULL;
PxScene*				gScene      = NULL;
ContactReportCallback gContactReportCallback;
RenderItem* ejeXItem;
RenderItem* ejeYItem;
RenderItem* ejeZItem;
RenderItem* centroItem;
std::vector<Projectile*> projectiles;
ParticleGen* fuente;
ParticleGen* fuego;
ParticleGen* niebla;
ParticleGen* torbellino;
ParticleGen* confetiIzq = nullptr;
ParticleGen* confetiDer = nullptr;
ForceSys* fs = new ForceSys();
ParticleSys* listaGenParticles = new ParticleSys(fs);
GravityForceGen* gravityGen = new GravityForceGen(Vector3D(0, -10, 0));
//WindForceGen* windGen = new WindForceGen({ 5, 0, 0 }, 0.2f);
TorbellinoForceGen* torbellinoGen = new TorbellinoForceGen(Vector3D(0.0f, 0.0f, 0.0f),
	10.0f,15.0f,Vector3D(0,10,0), 8.0f, 40.0f);
ExplosionForce* explosion = new ExplosionForce({ 0, 0, 0 }, 50.0f, 50000.0f, 7.0f);
std::vector<RenderItem*> campo;

////////////////////////////////////////////
///////////////////////////Cosas juego
TiroCanasta* tiroCanasta = nullptr;


void crearCampo() {

	//CAMPO
	Vector3D esquina1(-15.0f, 0.0f, 10.0f);
	Vector3D esquina2(15.0f, 0.0f,10.0f);
	Vector3D esquina3(-15.0f, 0.0f, -25.0f);
	Vector3D esquina4(15.0f, 0.0f, -25.0f);
	Vector3D canastaPos(0.0f, 3.05f, -23.0f);


	RenderItem* r1 = new RenderItem(CreateShape(PxSphereGeometry(0.5f)),new PxTransform(esquina1.getX(), esquina1.getY(), esquina1.getZ()),Vector4(1, 1, 0, 1));
	RegisterRenderItem(r1);
	campo.push_back(r1);

	RenderItem* r2 = new RenderItem(CreateShape(PxSphereGeometry(0.5f)),new PxTransform(esquina2.getX(), esquina2.getY(), esquina2.getZ()),Vector4(1, 1, 0, 1));
	RegisterRenderItem(r2);
	campo.push_back(r2);

	RenderItem* r3 = new RenderItem(CreateShape(PxSphereGeometry(0.5f)),new PxTransform(esquina3.getX(), esquina3.getY(), esquina3.getZ()),Vector4(1, 1, 0, 1));
	RegisterRenderItem(r3);
	campo.push_back(r3);

	RenderItem* r4 = new RenderItem(CreateShape(PxSphereGeometry(0.5f)),new PxTransform(esquina4.getX(), esquina4.getY(), esquina4.getZ()),Vector4(1, 1, 0, 1));
	RegisterRenderItem(r4);
	campo.push_back(r4);

	RenderItem* canasta = new RenderItem(CreateShape(PxSphereGeometry(0.6f)),new PxTransform(canastaPos.getX(), canastaPos.getY(), canastaPos.getZ()),Vector4(1, 0, 0, 1));
	RegisterRenderItem(canasta);
	campo.push_back(canasta);

	//CAMARA
	PxVec3 canastaPosPx(0.0f, 3.05f, 10.0f);
	PxVec3 posicionCam(0.0f, 3.0f, 14.0f);
	PxVec3 direccion = (canastaPosPx - posicionCam).getNormalized();

	GetCamera()->setPos(posicionCam);
	GetCamera()->setDir(direccion);

	//CONFETI
	Vector3D posConfetiIzq = canastaPos + Vector3D(-5.0f, -1.0f, 0.0f);
	Vector3D posConfetiDer = canastaPos + Vector3D(5.0f, -1.0f, 0.0f);

	confetiIzq = new ParticleGen(posConfetiIzq,Vector3D(0, 5, 0),Vector3D(5, 5, 5),0.98f,1.0f,20.0f,1.0f,Vector4(1, 1, 0, 1),0.3f,1.0f,fs);

	confetiDer = new ParticleGen(posConfetiDer,Vector3D(0, 5, 0),Vector3D(5, 5, 5),0.98f,1.0f,20.0f,1.0f,Vector4(1, 0, 1, 1),0.3f,1.0f,fs);
	listaGenParticles->addParticle(confetiIzq);
	listaGenParticles->addParticle(confetiDer);

}
void crearEjes() {
	Vector3D ejeX(10.0f, 0.0f, 0.0f); 
	Vector3D ejeY(0.0f, 10.0f, 0.0f); 
	Vector3D ejeZ(0.0f, 0.0f, 10.0f);
	Vector3D centro(0.0f, 0.0f, 0.0f);

	ejeXItem = new RenderItem(CreateShape(PxSphereGeometry(2)),new PxTransform(ejeX.getX(), ejeX.getY(), ejeX.getZ()),Vector4(1, 0, 0, 1));
	RegisterRenderItem(ejeXItem);

	 ejeYItem = new RenderItem(CreateShape(PxSphereGeometry(2)), new PxTransform(ejeY.getX(), ejeY.getY(), ejeY.getZ()), Vector4(0, 1, 0, 1));
	 RegisterRenderItem(ejeYItem);

	
	 ejeZItem = new RenderItem(CreateShape(PxSphereGeometry(2)), new PxTransform(ejeZ.getX(), ejeZ.getY(), ejeZ.getZ()), Vector4(0, 0, 1, 1));
	 RegisterRenderItem(ejeZItem);

	 centroItem = new RenderItem(CreateShape(PxSphereGeometry(2)), new PxTransform(centro.getX(), centro.getY(), centro.getZ()), Vector4(1, 1, 1, 1));

	RegisterRenderItem(centroItem);

}


// Initialize physics engine
void initPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport,PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(),true,gPvd);

	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	// For Solid Rigids +++++++++++++++++++++++++++++++++++++
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;
	gScene = gPhysics->createScene(sceneDesc);
	



	tiroCanasta = new TiroCanasta(fs);
	crearCampo();
	//fuente = new ParticleGen(Vector3D(0, 50, 0),Vector3D(0, 20, 0),Vector3D(5, 5, 5),Vector3D(0.0f, -10.0f, 0.0f),0.99f,4.0f,50.0f,0.1f, Vector4(0, 0, 1, 1),0.5f);
	//fuego = new ParticleGen(Vector3D(0, 50, 0), Vector3D(0, 25, 0), Vector3D(10, 10, 10), Vector3D(0.0f, -10.0f, 0.0f), 0.96f, 2.0f, 150.0f, 0.1f, Vector4(1, 0, 0, 1), 0.5f);
	niebla = new ParticleGen(Vector3D(0, 0, 0), Vector3D(0, 0, 0), Vector3D(1, 1, 1),
		0.999f, 20.0f, 50.0f, 10.0f,Vector4(0.6f, 0.6f, 0.6f, 1.0f), 0.5f,1.0f, fs);
	
	torbellino = new ParticleGen(Vector3D(0, 10, 0), Vector3D(0, 0, 0), Vector3D(10, 5, 10), 0.999f, 25.0f, 80.0f, 15.0f, Vector4(0.7f, 0.7f, 1.0f, 1.0f), 1.0f, 2.0f, fs);
	//listaGenParticles->addParticle(torbellino);
	//torbellino->addForce(torbellinoGen);
	//niebla->addForce(explosion);

	//particula = new Particle(Vector3D(0, 0, 0), Vector3D(1, 0, 0), Vector3D(0, 1, 0), 0.998);
	
	}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);

	gScene->simulate(t);
	gScene->fetchResults(true);

	tiroCanasta->update(t);
	tiroCanasta->renderBarraCarga();


	for (auto p : projectiles) {
		p->integrate(t);
	}
	//fuente->update(t);
	//fuego->update(t);
	listaGenParticles->update(t);
	fs->update(t);

}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{

	PX_UNUSED(interactive);
	
	for (auto p : projectiles) {
		delete p; 
	}
	delete tiroCanasta;
	for (auto c : campo) {
		RegisterRenderItem(c);
	}
	//delete particula;

	// Rigid Body ++++++++++++++++++++++++++++++++++++++++++
	gScene->release();
	gDispatcher->release();
	// -----------------------------------------------------
	gPhysics->release();	
	PxPvdTransport* transport = gPvd->getTransport();
	gPvd->release();
	transport->release();
	
	gFoundation->release();
	}

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);

	switch(toupper(key))
	{
	//case 'B': break;
	//case ' ':	break;
	case '1': // pelota baloncesto
		tiroCanasta->cambiarBola(1);
		break;
	case '2':
	{
		tiroCanasta->cambiarBola(2);

		//explosion->explode();
		break;
	}case '3': 
		tiroCanasta->cambiarBola(3);
		break;
	case ' ':

		tiroCanasta->cargarDisparo();
		break;
	case '4':
		tiroCanasta->activarExplosion();
		break;
	default:
		break;
	}
}
void keyRelease(unsigned char key)
{
	switch (toupper(key))
	{
	case ' ':
		tiroCanasta->soltarDisparo();
		break;
	default:
		break;
	}
}


void onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
	PX_UNUSED(actor1);
	PX_UNUSED(actor2);
}




int main(int, const char*const*)
{
#ifndef OFFLINE_EXECUTION 
	extern void renderLoop();
	renderLoop();
#else
	static const PxU32 frameCount = 100;
	initPhysics(false);
	for(PxU32 i=0; i<frameCount; i++)
		stepPhysics(false);
	cleanupPhysics(false);
#endif

	return 0;
}