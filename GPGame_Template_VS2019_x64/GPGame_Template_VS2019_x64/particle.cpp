#include "particle.h"
#include <iostream>
using namespace std;
#include "shapes.h"
#include "graphics.h"
#include <glm\gtx\transform.hpp>

    int id;

    //Default Constructor 
    Particle::Particle()
    {
        id = -1;
        lifespan = 1;
        dead = false;
    }

    void Particle::init(glm::vec3 vec) {
        vec0.x = vec.x;
        vec0.y = vec.y;
        vec0.z = vec.z;
    }   

    void Particle::load() {
        //active = 1;
        //dead = false;
        shapePcl.Load();
        shapePcl.fillColor = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
    }
