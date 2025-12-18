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

#include "GameEffectManager.h"
#include "EffectNormal.h"
#include "EffectBasketLado.h"
#include "EffectWind.h"
#include "EffectBolaPequeña.h"
#include "EfectoBolaGrande.h"
#include "EfectoMuelle.h"
#include "EfectoSolidosVoladores.h"

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
CanastaManager* basketManager = nullptr;
GameEffectManager* effectManager = nullptr;

ParticleGen* confetiIzq = nullptr;
ParticleGen* confetiDer = nullptr;

ForceSys* fs = new ForceSys();
SolidSys* sistemaSolidos = new SolidSys();

ParticleSys* listaGenParticles = new ParticleSys(fs);

std::vector<RenderItem*> campo;
GameState gameState = STATE_MENU;
double tiempoJuego = 60.0;
int puntos = 0;
std::string display_text_puntos = "";
std::string display_text_tiempo = "";
std::string display_text_title= "";
std::string display_text_subtitle="";
std::string display_text_effect = "";




void crearCampo() {
	//CAMARA
	Vector3D canastaPosPx;
	for (auto a : basketManager->getBaskets()) {
		basketManager->moveAll(Vector3D(0, 0, 0));
		canastaPosPx = a->getPosition();
		PxVec3 canastaPos = PxVec3(canastaPosPx.getX(), canastaPosPx.getY(), canastaPosPx.getZ());
		PxVec3 posicionCam(0.0f, 8.0f, 90.0f);
		PxVec3 direccion = (canastaPos - posicionCam).getNormalized();

		GetCamera()->setPos(posicionCam);
		GetCamera()->setDir(direccion);

	}
	

	//SUELO

	PxTransform poseSuelo(PxVec3(0, -1, 0));
	PxRigidStatic* suelo = gPhysics->createRigidStatic(poseSuelo);
	PxMaterial* material = gPhysics->createMaterial(1.0f, 1.0f, 0.0f);
	PxShape* shapeSuelo = CreateShape(PxBoxGeometry(50, 1, 100), material);
	suelo->attachShape(*shapeSuelo);

	gScene->addActor(*suelo);

	new RenderItem(shapeSuelo, suelo, Vector4(0.0f, 0.5f, 1.0f, 1.0f));

	Vector3D posConfetiIzq = canastaPosPx + Vector3D(-10.0f, -1.0f, 0.0f);
	Vector3D posConfetiDer = canastaPosPx + Vector3D(10.0f, -1.0f, 0.0f);
	confetiIzq = new ParticleGen(posConfetiIzq, Vector3D(0, 5, 0), Vector3D(2, 2, 2), 0.98f, 4.0f, 80.0f, 1.0f, Vector4(1, 1, 0, 1), 2.0f, 1.0f, fs, TDist::NORMAL);
	confetiDer = new ParticleGen(posConfetiDer, Vector3D(0, 5, 0), Vector3D(2, 2, 2), 0.98f, 4.0f,80.0f, 1.0f, Vector4(1, 0, 1, 1), 2.0f, 1.0f, fs, TDist::UNIFORME);
	
	listaGenParticles->addParticle(confetiIzq);
	listaGenParticles->addParticle(confetiDer);
	confetiDer->togglePausar();
	confetiIzq->togglePausar();
}
void crearEfectos() {
	effectManager = new GameEffectManager(15.0f);

	effectManager->addEffect(new EffectNormal(tiroCanasta, basketManager, sistemaSolidos));
	effectManager->addEffect(new EffectBasketLado(basketManager));
	effectManager->addEffect(new EffectWind(tiroCanasta));
	effectManager->addEffect(new EffectBolaPequeña(tiroCanasta));
	effectManager->addEffect(new EfectoBolaGrande(tiroCanasta));
	effectManager->addEffect(new EfectoMuelle(basketManager, fs));
	effectManager->addEffect(new EfectoSolidosVoladores(sistemaSolidos,gPhysics,gScene,gMaterial));
	effectManager->start();
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
	crearEfectos();
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

		GameEffect* ef = effectManager->getActiveEffect();
		if (ef) {
			display_text_effect = "Efecto: " + ef->getName();
		}
		else {
			display_text_effect = "Efecto: Ninguno";
		}

		if (tiempoJuego <= 0) {
			tiempoJuego = 0;
			if (puntos >= 10) gameState = STATE_WIN;
			else gameState = STATE_LOSE;

			return;
		}
		effectManager->update((float)t);

		tiroCanasta->update(t);
		tiroCanasta->renderBarraCarga();

		listaGenParticles->update(t);
		basketManager->update(t);
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
		display_text_title = "BALONTIEMPO";
		display_text_subtitle = "Pulsa E para empezar";
		if (!confetiDer->getPausar() ) {
			confetiDer->togglePausar();
			confetiIzq->togglePausar();
		}
		

	}
	if (gameState == STATE_LOSE) {
		
		display_text_title = "GAME OVER";
		display_text_subtitle = "Pulsa E para volver al menu";
		display_text_puntos = "Puntos finales: " + std::to_string(puntos);
		display_text_effect = "";
		display_text_tiempo = "";
	}
	if (gameState == STATE_WIN) {
		
		display_text_title = "¡HAS GANADO!";
		display_text_subtitle = "Pulsa E para volver al menu";
		display_text_puntos = "Puntos finales: " + std::to_string(puntos);
		display_text_effect = "";
		display_text_tiempo = "";

		listaGenParticles->update(t);

		confetiDer->togglePausar();
		confetiIzq->togglePausar();
	}

}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{

	PX_UNUSED(interactive);
	delete fs;
	delete effectManager;
	delete tiroCanasta;
	delete basketManager;
	delete sistemaSolidos;
	delete confetiIzq;
	delete confetiDer;

	for (auto c : campo) {
		delete c;
	}
	campo.clear();
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
			tiempoJuego = 60.0;
			gameState = STATE_GAME;
		}
		else if (gameState == STATE_WIN || gameState == STATE_LOSE) {
			gameState = STATE_MENU;
			effectManager->estadoNormal();
		}
		break;
	default:
		break;
	}
	if (gameState == STATE_GAME) {
		switch (toupper(key))
		{
		case ' ':

			tiroCanasta->cargarDisparo();
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