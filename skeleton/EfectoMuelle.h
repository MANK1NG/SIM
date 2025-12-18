#pragma once
#include <unordered_map>
#include "GameEffect.h"
#include "CanastaManager.h"
#include "SpringForceGen.h"
class EfectoMuelle :
    public GameEffect
{
public:
    EfectoMuelle(CanastaManager* cm, ForceSys* fs);
    ~EfectoMuelle();
    void onEnter() override;
    void onExit() override;
    void update(float t) override;
    std::string EfectoMuelle::getName() override {
        return "Muelle";
    }
private:
    CanastaManager* basketMgr;
    ForceSys* fs;
    struct SpringData {
        Particle* anchor;
        SpringForceGenerator* spring;
    };
    std::unordered_map<Particle*, SpringData> springs;
    float k = 40.0f;
    float restLeght = 1.0;

};

