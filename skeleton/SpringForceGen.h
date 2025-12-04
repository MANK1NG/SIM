#pragma once
#include "ForceGen.h"
#include "core.hpp"

class SpringForceGenerator : public ForceGen {
public:
    SpringForceGenerator(double k, double resting_length, Particle* other);

     void updateForce(Particle* particle,double t)override ;

    inline void setK(double k) { _k = k; }
    inline double getK() const { return _k; }


    virtual ~SpringForceGenerator() {}

protected:
    double _k;
    double _resting_length;
    Particle* _other;
};
