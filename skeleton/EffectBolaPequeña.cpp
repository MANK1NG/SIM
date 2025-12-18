#include "EffectBolaPequeña.h"

EffectBolaPequeña::EffectBolaPequeña(TiroCanasta* tc)
	:tiro(tc)
{
}

void EffectBolaPequeña::onEnter()
{
	tiro->cambiarBola(3);
}

void EffectBolaPequeña::onExit()
{
	tiro->cambiarBola(1);
}
