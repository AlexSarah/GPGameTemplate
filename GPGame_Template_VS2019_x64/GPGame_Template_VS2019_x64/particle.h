#pragma once
#include "graphics.h"
#include "shapes.h"
class Particle
{

public:
    Sphere shapePcl;

    int active;

    bool dead;

    Particle();

    Particle(int x);

    void load();

    //void updatePcl(Graphics& myGraphics, float t);

    //void draw();

};

