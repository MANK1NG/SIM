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
#include "AnchoredSpringForceGen.h"
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


////////////////////////////////////////////
///////////////////////////Cosas juego
TiroCanasta* tiroCanasta = nullptr;

ParticleGen* confetiIzq = nullptr;
ParticleGen* confetiDer = nullptr;
ForceSys* fs = new ForceSys();
ParticleSys* listaGenParticles = new ParticleSys(fs);
TorbellinoForceGen* torbellinoGen = new TorbellinoForceGen(Vector3D(0.0f, 0.0f, 0.0f), 10.0f, 15.0f, Vector3D(0.0f, 2.05f, -23.0f), 40.0f, 60.0f);
std::vector<RenderItem*> campo;
GravityForceGen* gravityGen = new GravityForceGen(Vector3D(0, -10, 0));


Particle* springParticle = nullptr;
AnchoredSpringForceGen* anchoredSpring = nullptr;
Particle* A = nullptr;
Particle* B = nullptr;

SpringForceGenerator* springAB = nullptr;

void crearCampo() {
	//CAMARA
	PxVec3 canastaPosPx(0.0f, 3.05f, 10.0f);
	PxVec3 posicionCam(0.0f, 3.0f, 14.0f);
	PxVec3 direccion = (canastaPosPx - posicionCam).getNormalized();

	GetCamera()->setPos(posicionCam);
	GetCamera()->setDir(direccion);

	/*//CAMPO
	Vector3D esquina1(-15.0f, 0.0f, 10.0f);
	Vector3D esquina2(15.0f, 0.0f,10.0f);
	Vector3D esquina3(-15.0f, 0.0f, -25.0f);
	Vector3D esquina4(15.0f, 0.0f, -25.0f);
	Vector3D canastaPos(0.0f, 3.05f, -23.0f);


	RenderItem* r1 = new RenderItem(CreateShape(PxBoxGeometry(0.5f, 0.5f, 0.5f)), new PxTransform(esquina1.getX(), esquina1.getY(), esquina1.getZ()), Vector4(1, 1, 0, 1));
	RegisterRenderItem(r1);
	campo.push_back(r1);

	RenderItem* r2 = new RenderItem(CreateShape(PxBoxGeometry(0.5f, 0.5f, 0.5f)),new PxTransform(esquina2.getX(), esquina2.getY(), esquina2.getZ()),Vector4(1, 1, 0, 1));
	RegisterRenderItem(r2);
	campo.push_back(r2);

	RenderItem* r3 = new RenderItem(CreateShape(PxBoxGeometry(0.5f, 0.5f, 0.5f)),new PxTransform(esquina3.getX(), esquina3.getY(), esquina3.getZ()),Vector4(1, 1, 0, 1));
	RegisterRenderItem(r3);
	campo.push_back(r3);

	RenderItem* r4 = new RenderItem(CreateShape(PxBoxGeometry(0.5f, 0.5f, 0.5f)),new PxTransform(esquina4.getX(), esquina4.getY(), esquina4.getZ()),Vector4(1, 1, 0, 1));
	RegisterRenderItem(r4);
	campo.push_back(r4);

	RenderItem* canasta = new RenderItem(CreateShape(PxSphereGeometry(0.6f)),new PxTransform(canastaPos.getX(), canastaPos.getY(), canastaPos.getZ()),Vector4(1, 0, 0, 1));
	RegisterRenderItem(canasta);
	campo.push_back(canasta);

	
	//CONFETI
	Vector3D posConfetiIzq = canastaPos + Vector3D(-10.0f, -1.0f, 0.0f);
	Vector3D posConfetiDer =  canastaPos + Vector3D(10.0f, -1.0f, 0.0f);

	confetiIzq = new ParticleGen(posConfetiIzq,Vector3D(0, 5, 0),Vector3D(2,2, 2),0.98f,2.0f,40.0f,1.0f,Vector4(1, 1, 0, 1),0.3f,1.0f,fs, TDist::NORMAL);

	confetiDer = new ParticleGen(posConfetiDer,Vector3D(0, 5, 0),Vector3D(2, 2, 2),0.98f,2.0f,40.0f,1.0f,Vector4(1, 0, 1, 1),0.3f,1.0f,fs, TDist::UNIFORME);
	
	confetiDer->addForce(torbellinoGen);
	confetiIzq->addForce(torbellinoGen);

	listaGenParticles->addParticle(confetiIzq);
	listaGenParticles->addParticle(confetiDer);

	*/
	springParticle = new Particle(Vector3D(0, 5, 0),Vector3D(0, 0, 0),0.99f,400,Vector4(0, 1, 0, 1),4.0f,1.0f);
	A =  new Particle(Vector3D(-1, 5, 0), Vector3D(0, 0, 0), 0.99f, 9999, Vector4(1, 0, 0, 1), 1.0f, 1);
	B = new Particle(Vector3D(1, 5, 0), Vector3D(0, 0, 0), 0.99f, 9999, Vector4(0, 1, 0, 1), 1.0f, 1);
	anchoredSpring = new AnchoredSpringForceGen(7.0, 3.0, Vector3D(0, 8, 0));
	springAB = new SpringForceGenerator(4.0, 2.0, B);
	
	
	fs->addForce(springParticle, anchoredSpring);
	fs->addForce(A, springAB);
	fs->addForce(B, springAB);
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
	

	//tiroCanasta = new TiroCanasta(fs, listaGenParticles);
	crearCampo();
	}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);

	gScene->simulate(t);
	gScene->fetchResults(true);

	//tiroCanasta->update(t);
	//tiroCanasta->renderBarraCarga();

	//listaGenParticles->update(t);
	
	fs->update(t);
	springParticle->integrate(t);
	A->integrate(t);
	B->integrate(t);
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{

	PX_UNUSED(interactive);
	
	
	delete tiroCanasta;
	for (auto c : campo) {
		RegisterRenderItem(c);
	}

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

	case '1': 
		tiroCanasta->cambiarBola(1);
		break;
	case '2':
	{
		tiroCanasta->cambiarBola(2);

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
	case 'T':
		confetiDer->togglePausar();
		confetiIzq->togglePausar();
		break;
	case 'R':
		torbellinoGen->toggleActivo();
		break;
	case 'V':
		
		tiroCanasta->getZonaViento()->toggleActivo();
		break;

	case '+':
		anchoredSpring->setK(anchoredSpring->getK() + 2.0);
		springAB->setK(springAB->getK() + 2.0);
		break;

	case '-':
		anchoredSpring->setK(anchoredSpring->getK() - 2.0);
		springAB->setK(springAB->getK() - 2.0);
		break;

	case 'F':
		springParticle->addForce(Vector3D(0, 100, 0));
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