#include "particle.h"
#include <iostream>
using namespace std;
#include "shapes.h"
#include "graphics.h"
#include <glm\gtx\transform.hpp>

    int id;
    /*
    struct particle                      // Create A Structure For Particle
    {
        bool    active;                 // Active (Yes/No)
        Shapes shapePcl;

        float   x;                  // X Position
        float   y;                  // Y Position
        float   z;                  // Z Position

        float   xi;                 // X Direction
        float   yi;                 // Y Direction
        float   zi;                 // Z Direction

    };                      // Particles Structure
    */

    //Default Constructor 
    Particle::Particle()
    {
        cout << "Default Constructor called" << endl;
        id = -1;

    }

    //Parametrized Constructor 
    Particle::Particle(int x)
    {
        cout << "Parametrized Constructor called" << endl;
        id = x;
    }

    void Particle::load() {
        active = 1;
        dead = false;
        shapePcl.Load();
        shapePcl.fillColor = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
    }
/*
    void Particle::updatePcl(Graphics &myGraphics, float t) {
        glm::mat4 mv_matrix_sphere =
            glm::translate(glm::vec3(2.0f, 0.5f, 0.0f)) *
            glm::mat4(1.0f);
            shapePcl.mv_matrix = myGraphics.viewMatrix * mv_matrix_sphere;
            shapePcl.proj_matrix = myGraphics.proj_matrix;
    }

    void Particle::draw() {
        shapePcl.Draw();
    }
*/