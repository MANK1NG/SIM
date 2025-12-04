#pragma once
#include "SpringForceGen.h"

class AnchoredSpringForceGen :
    public SpringForceGenerator
{
public:

    AnchoredSpringForceGen(double k, double resting, const Vector3D& anchor_pos);
    ~AnchoredSpringForceGen();
};

