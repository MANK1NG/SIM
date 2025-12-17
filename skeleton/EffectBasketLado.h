#pragma once
#include "GameEffect.h"
#include "CanastaManager.h"
#include <cmath>
class EffectBasketLado :
    public GameEffect
{
public:
    EffectBasketLado(CanastaManager* cm);
    void update(float t) override;
private:
    CanastaManager* basketMgr;
    float time;
};

