#pragma once
#include "GameEffect.h"
#include "CanastaManager.h"
#include <cmath>
#include <random>
class EffectBasketLado :
    public GameEffect
{
public:
    EffectBasketLado(CanastaManager* cm);
    void onEnter() override;
    void update(float t) override;
    void onExit() override;
    std::string EffectBasketLado::getName() override {
        return "LADO A LADO";
    }
private:
    CanastaManager* basketMgr;
    int dir;
    float force = 4.0f;
    std::mt19937 gen;
};

