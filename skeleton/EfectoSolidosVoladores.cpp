#include "EfectoSolidosVoladores.h"



EfectoSolidosVoladores::EfectoSolidosVoladores(SolidSys* sys, physx::PxPhysics* phys_, physx::PxScene* scene_, physx::PxMaterial* mat_)
	 : solidSys(sys), phys(phys_),scene(scene_),mat(mat_)
{

}

void EfectoSolidosVoladores::onEnter()
{
	Vector3D origen(50.0f, 15.0f, 30.0f);
	Vector3D vel(-60.0f, 0.0f, 0.0f);
	gen = new SolidGen(origen, vel, 0.7f, mat, phys, scene);

	solidSys->addGenerator(gen);
}

void EfectoSolidosVoladores::onExit()
{
	solidSys->removeGenerator(gen);
	gen = nullptr;
}
