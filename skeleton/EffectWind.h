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
    std::string EffectWind::getName() override {
        return "VIENTO";
    }
private:
    TiroCanasta* tiro;
};

