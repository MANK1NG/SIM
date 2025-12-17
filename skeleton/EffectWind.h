#pragma once
#include "GameEffect.h"
#include "TiroCanasta.h"
class EffectWind :
    public GameEffect
{
public:
    EffectWind(TiroCanasta* tc);
    void onEnter() override;
    void onExit() override;
private:
    TiroCanasta* tiro;
};

