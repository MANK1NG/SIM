#pragma once
#include "SolidGen.h"
#include <vector>

class SolidSys {
public:
    SolidSys();
    ~SolidSys();

    void addGenerator(SolidGen* sg);
    void update(float dt);

private:
    std::vector<SolidGen*> generadores;
};