#include "ForceSys.h"
#include "ForceGen.h"

ForceSys::~ForceSys() {}
void ForceSys::addForce(Particle* p, ForceGen* fg)
{
	fuerzasGen[p].push_back(fg);
}

void ForceSys::removeForces(Particle* p)
{
    auto it = fuerzasGen.find(p);
    if (it != fuerzasGen.end()) {
        fuerzasGen.erase(it);
    }
}


void ForceSys::update(float dt) {
    std::vector<Particle*> aEliminar;

    for (auto& par : fuerzasGen) {
        Particle* p = par.first;
        if (p == nullptr || !p->isAlive()) {
            aEliminar.push_back(p);
            continue;
        }

        for (auto fg : par.second) {
            if (fg->getActivo()) {
            fg->updateForce(p, dt);
            fg->update(dt);
            }
        }
        
    }

    for (auto p : aEliminar) {
        fuerzasGen.erase(p);
    }
}