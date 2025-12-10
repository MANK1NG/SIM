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
#include "BuoyancyForceGen.h"
#include "SolidGen.h"
#include "SolidSys.h"
#include "CanastaManager.h"
#include "GameState.h"

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
SolidSys* sistemaSolidos = new SolidSys();
CanastaManager* basketManager = nullptr;
int puntos = 0;
std::string display_text_puntos = "";
std::string display_text_tiempo = "";
std::string display_text_title= "";
std::string display_text_subtitle="";

GameState gameState = STATE_MENU;
double tiempoJuego = 30.0;

void crearCampo() {
	//CAMARA
	PxVec3 canastaPosPx(0.0f, 20.0f, -30.0f);
	PxVec3 posicionCam(0.0f, 3.0f, 100.0f);
	PxVec3 direccion = (canastaPosPx - posicionCam).getNormalized();

	GetCamera()->setPos(posicionCam);
	GetCamera()->setDir(direccion);

	//SUELO
	PxTransform poseSuelo(PxVec3(0, -1, 0));
	PxRigidStatic* suelo = gPhysics->createRigidStatic(poseSuelo);

	PxShape* shapeSuelo = CreateShape(PxBoxGeometry(100, 1, 100));
	suelo->attachShape(*shapeSuelo);

	gScene->addActor(*suelo);

	new RenderItem(shapeSuelo, suelo, Vector4(1, 1, 0, 1.0));
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
	basketManager = new CanastaManager(gPhysics, gScene);
	basketManager->addBasket();

	tiroCanasta = new TiroCanasta(fs, listaGenParticles, gPhysics,gScene);
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
	if (gameState == STATE_GAME) {
		display_text_title = "";
		display_text_subtitle = "";

		tiempoJuego -= t;
		display_text_puntos = "Puntos: " + std::to_string(puntos);
		display_text_tiempo = "Tiempo: " + std::to_string((int)tiempoJuego);
		if (tiempoJuego <= 0) {
			tiempoJuego = 0;
			if (puntos >= 20) gameState = STATE_WIN;
			else gameState = STATE_LOSE;

			return;
		}
		tiroCanasta->update(t);
		tiroCanasta->renderBarraCarga();

		listaGenParticles->update(t);

		fs->update(t);
		sistemaSolidos->update(t);
		if (basketManager->getBaskets().size() > 0) {
			Canasta* scoredCanasta = tiroCanasta->checkScored(basketManager->getBaskets());

			if (scoredCanasta != nullptr) {
				
				basketManager->removeBasket(scoredCanasta);
				basketManager->addBasket();

				puntos++;
			}
		}
	}
	if (gameState == STATE_MENU) {
		display_text_title = "MI SUPER JUEGO";
		display_text_subtitle = "Pulsa E para empezar";
	}
	if (gameState == STATE_LOSE) {
		display_text_title = "GAME OVER";
		display_text_subtitle = "Pulsa E para volver al menú";
		display_text_puntos = "Puntos finales: " + std::to_string(puntos);
	}
	if (gameState == STATE_WIN) {
		display_text_title = "¡HAS GANADO!";
		display_text_subtitle = "Pulsa E para volver al menu";
		display_text_puntos = "Puntos finales: " + std::to_string(puntos);
	}

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

	switch (toupper(key))
	{
	case 'E':
		if (gameState == STATE_MENU) {
			puntos = 0;
			tiempoJuego = 30.0;
			gameState = STATE_GAME;
		}
		else if (gameState == STATE_WIN || gameState == STATE_LOSE) {
			gameState = STATE_MENU;
		}
		break;
	default:
		break;
	}
	if (gameState == STATE_GAME) {
		switch (toupper(key))
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
		default:
			break;
		}
	}
	
	
}
void keyRelease(unsigned char key)
{
	if (gameState == STATE_GAME) {
		switch (toupper(key))
		{
		case ' ':
 			tiroCanasta->soltarDisparo();
			break;
		default:
			break;
		}
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