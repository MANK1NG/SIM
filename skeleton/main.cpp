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
//Particle* particula;
//Projectile* proyectil;
RenderItem* centroItem;
std::vector<Projectile*> projectiles;
ParticleGen* fuente;

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

void disparar()
{
	PxVec3 eye = GetCamera()->getEye();
	PxVec3 dir = GetCamera()->getDir();

	Vector3D pos(eye.x, eye.y, eye.z);
	Vector3D dirVec(dir.x, dir.y, dir.z);

	Vector3D velSim = dirVec.multEscalar(5.0f); 
	

	Projectile* p = new Projectile(pos, Vector3D(0, 0, 0), 0.995f, 0.625f, Vector3D(8, 20, 0), velSim, Vector3D(0, -9.8f, 0));

	projectiles.push_back(p);
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
	
	
	crearEjes();

	fuente = new ParticleGen(Vector3D(0, 50, 0),Vector3D(0, 20, 0),Vector3D(5, 5, 5),Vector3D(0.0f, -9.8f, 0.0f),0.99f,5.0f,50.0f);
	
	//particula = new Particle(Vector3D(0, 0, 0), Vector3D(1, 0, 0), Vector3D(0, 1, 0), 0.998);
	

	//IMPORTANTEPARA PRACTICA 1.2 : 
	// GetCamera()->GetDir(); -> direccion camara
	//GetCamera()->getEye(); -> centro de la camara
	
	//sphere12 = new RenderItem(CreateShape(PxSphereGeometry(2)), new PxTransform(1, 1, 1), { 1,1,1,1 });
	//RegisterRenderItem(sphere12);
	}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);

	gScene->simulate(t);
	gScene->fetchResults(true);
	//particula->integrate(t);
	for (auto p : projectiles) {
		p->integrate(t);
	}
	fuente->update(t);
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{

	PX_UNUSED(interactive);
	DeregisterRenderItem(centroItem);
	DeregisterRenderItem(ejeZItem);
	DeregisterRenderItem(ejeYItem);
	DeregisterRenderItem(ejeXItem);
	for (auto p : projectiles) {
		delete p; 
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
		// speedSimulada (m/s), velRealMagnitude (m/s), masaReal (kg)
		disparar();
		break;
	case ' ':
	{
		break;
	}
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