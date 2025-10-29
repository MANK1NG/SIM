#include "ForceSys.h"
#include "ForceGen.h"

ForceSys::~ForceSys() {}
void ForceSys::addForce(Particle* p, ForceGen* fg)
{
	fuerzasGen[p].push_back(fg);
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
            fg->updateForce(p, dt);
            fg->update(dt);
        }
        
    }

    for (auto p : aEliminar) {
        fuerzasGen.erase(p);
    }
}