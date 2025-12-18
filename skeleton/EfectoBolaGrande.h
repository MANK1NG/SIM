#pragma once
#include "GameEffect.h"
#include "TiroCanasta.h"
class EfectoBolaGrande :
    public GameEffect
{
public:
    EfectoBolaGrande(TiroCanasta* tc);
    void onEnter() override;
    void onExit() override;

    std::string EfectoBolaGrande::getName()override  {
        return "PELOTA GRANDE";
    }
private:
    TiroCanasta* tiro;
};

