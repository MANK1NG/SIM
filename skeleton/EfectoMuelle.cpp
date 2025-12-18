#include "EfectoMuelle.h"

EfectoMuelle::EfectoMuelle(CanastaManager* cm, ForceSys* fs_)
    : basketMgr(cm), fs(fs_)
{
   
}

EfectoMuelle::~EfectoMuelle()
{
    onExit();
}

void EfectoMuelle::onEnter()
{
    springs.clear();
}

void EfectoMuelle::onExit()
{
    for (auto& par : springs)
    {
        fs->removeForces(par.first);
        par.first->setVelocity(Vector3D(0, 0, 0));
        delete par.second.spring;
        delete par.second.anchor;
    }

    springs.clear();
}

void EfectoMuelle::update(float t){
    for (auto* b : basketMgr->getBaskets())
    {
        Particle* volante = b->getVolante();

        if (springs.find(volante) != springs.end()) {
            continue;
        }

        Particle* anchor = new Particle(volante->getPos() + Vector3D(0, 5, 0),Vector3D(0, 0, 0),0.98f,99999.0f,
            Vector4(0, 0, 0, 0),0.1f,1.0f);

        auto* spring = new SpringForceGenerator(k, restLeght, anchor);
        fs->addForce(volante, spring);

        springs[volante] = { anchor, spring };
    }

    for (auto it = springs.begin(); it != springs.end(); )
    {
        Particle* p = it->first;
        bool sigue = false;

        for (auto* b : basketMgr->getBaskets())
        {
            if (b->getVolante() == p) {
                sigue = true;
                break;
            }
        }

        if (!sigue)
        {
            fs->removeForces(p);
            delete it->second.spring;
            delete it->second.anchor;
            it = springs.erase(it);
        }
        else {
            ++it;
        }
    }
}
