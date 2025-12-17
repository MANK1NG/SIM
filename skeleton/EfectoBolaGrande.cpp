#include "EfectoBolaGrande.h"

EfectoBolaGrande::EfectoBolaGrande(TiroCanasta* tc)
	:tiro(tc)
{
}

void EfectoBolaGrande::onEnter()
{
	tiro->cambiarBola(2);
}
