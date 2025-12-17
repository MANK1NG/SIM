#include "EffectBasketLado.h"

EffectBasketLado::EffectBasketLado(CanastaManager* cm)
	:basketMgr(cm), time(0.0f)
{
}

void EffectBasketLado::update(float t)
{
	time += t;
	float dx = sin(time * 2.0f) * t * 5.0f;
	basketMgr->moveAll(Vector3D(dx, 0, 0));
}
