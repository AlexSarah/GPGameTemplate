#pragma once
#include "graphics.h"
#include "shapes.h"
class Particle
{

public:
    Sphere shapePcl;

    glm::vec3 vec0;

    int  lifespan;

    bool dead;

    Particle();

    Particle(int x);

    void init(glm::vec3 vec);

    void load();
};

