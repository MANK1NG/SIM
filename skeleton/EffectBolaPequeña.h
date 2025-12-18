#pragma once
#include "GameEffect.h"
#include "TiroCanasta.h"
class EffectBolaPequeña :
    public GameEffect
{
public:
    EffectBolaPequeña(TiroCanasta* tc);
    void onEnter() override;
    void onExit() override;

    std::string EffectBolaPequeña::getName() override {
        return "PELOTA PEQUENA";
    }
private:
    TiroCanasta* tiro;
};

