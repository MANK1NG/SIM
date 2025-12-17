#pragma once
#include "GameEffect.h"
#include "TiroCanasta.h"
class EfectoBolaGrande :
    public GameEffect
{
public:
    EfectoBolaGrande(TiroCanasta* tc);
    void onEnter() override;
private:
    TiroCanasta* tiro;
};

