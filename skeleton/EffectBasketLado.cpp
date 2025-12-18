#include "EffectBasketLado.h"
EffectBasketLado::EffectBasketLado(CanastaManager* cm)
	:basketMgr(cm) , gen(std::random_device{}())
{
}

void EffectBasketLado::onEnter()
{
    std::uniform_int_distribution<> dis(0, 1);
    dir = (dis(gen) == 0) ? -1 : 1;
}

void EffectBasketLado::update(float t)
{
    for (auto* b : basketMgr->getBaskets())
    {
    Particle* p = b->getVolante();

    Vector3D pos = p->getPos();

    if (pos.getX() >= 15.0f) dir = -1;
    if (pos.getX() <= -15.0f) dir = 1;

    p->clearForce();
    p->addForce(Vector3D(dir * force*0.98, 0, 0));
    }
}

void EffectBasketLado::onExit()
{
    for (auto* b : basketMgr->getBaskets())
    {
        b->getVolante()->clearForce();
        b->getVolante()->setVelocity(Vector3D(0, 0, 0));

    }
}
