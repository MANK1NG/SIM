#pragma once
#include "GameEffect.h"
#include "TiroCanasta.h"
#include "CanastaManager.h"
#include "SolidSys.h"
class EffectNormal :
    public GameEffect
{
public:
    EffectNormal(TiroCanasta* tc, CanastaManager* cm, SolidSys* ss);
    void onEnter() override;
private:
    TiroCanasta* tiro;
    CanastaManager* basketMgr;
    SolidSys* solids;
};

