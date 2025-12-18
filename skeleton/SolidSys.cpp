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
void SolidSys::removeGenerator(SolidGen* sg)
{
    if (sg) {
        sg->desactivar();
    }
}

void SolidSys::update(float dt)
{
    for (auto g : generadores) {
        if (g) {
            g->update(dt);

        }
    }
    for(auto it = generadores.begin(); it != generadores.end(); ) {
        if (*it == nullptr || !(*it)->isActive()) {
            delete* it;
            it = generadores.erase(it);
        }
        else {
            ++it;
        }
    }
}