#pragma once
#include "GameEffect.h"
#include "SolidSys.h"
class EfectoSolidosVoladores :
    public GameEffect
{
public:
    EfectoSolidosVoladores(SolidSys* sys,physx::PxPhysics* phys,physx::PxScene* scene,physx::PxMaterial* mat);
    void onEnter() override;
    void onExit() override;
    std::string EfectoSolidosVoladores::getName() override {
        return "SOLIDOS VOLADORES";
    }
private:
    SolidSys* solidSys;
    SolidGen* gen;
    physx::PxPhysics* phys;
    physx::PxScene* scene; 
    physx::PxMaterial* mat;
};




