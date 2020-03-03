#pragma once
#include "graphics.h"
#include "shapes.h"
class Particle
{

public:
    Shapes shapePcl;

    float orientation;

    glm::vec3 pos0;

    glm::vec3 position;

    int  lifespan;

    bool dead;

    Particle();

    void init(glm::vec3 vec, float o, Shapes shape);

    Particle(int x);

    void load();

    void update();

    void setColor();

    float birthTime;

    int id;
};

