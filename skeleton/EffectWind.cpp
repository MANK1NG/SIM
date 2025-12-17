#include "EffectWind.h"
#include <iostream>

EffectWind::EffectWind(TiroCanasta* tc)
	:tiro(tc)
{
}

void EffectWind::onEnter()
{
	tiro->getZonaViento()->toggleActivo();

}

void EffectWind::onExit()
{
	tiro->getZonaViento()->toggleActivo();

}
