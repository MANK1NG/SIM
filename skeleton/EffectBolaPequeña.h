#pragma once
#include "GameEffect.h"
#include "TiroCanasta.h"
class EffectBolaPequeña :
    public GameEffect
{
public:
    EffectBolaPequeña(TiroCanasta* tc);
    void onEnter() override;
private:
    TiroCanasta* tiro;
};

