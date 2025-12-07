#include "SolidSys.h"

SolidSys::SolidSys() {}

SolidSys::~SolidSys()
{
    for (auto g : generadores) {
        delete g;
    }
}

void SolidSys::addGenerator(SolidGen* sg)
{
    generadores.push_back(sg);
}

void SolidSys::update(float dt)
{
    for (auto g : generadores) {
        g->update(dt);
    }
}