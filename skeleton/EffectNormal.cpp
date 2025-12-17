#include "EffectNormal.h"

EffectNormal::EffectNormal(TiroCanasta* tc, CanastaManager* cm, SolidSys* ss)
	:tiro(tc), basketMgr(cm), solids(ss)
{
}

void EffectNormal::onEnter()
{
	
	tiro->cambiarBola(1);
}
