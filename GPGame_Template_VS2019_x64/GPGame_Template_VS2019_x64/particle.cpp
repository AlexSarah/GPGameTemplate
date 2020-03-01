#include "particle.h"
#include <iostream>
using namespace std;
#include "shapes.h"
#include "graphics.h"
#include <glm\gtx\transform.hpp>
#include "emitter.h"
#define rad glm::radians

    int id;

    //Default Constructor 
    Particle::Particle()
    {
        id = -1;
        lifespan = 47;
        dead = true;
    }

    void Particle::init(glm::vec3 vec,float o) {
        pos0.x = vec.x;
        pos0.y = vec.y;
        pos0.z = vec.z;
        position.x = pos0.x;
        position.y = pos0.y;
        position.z = pos0.z;
        orientation = o;
    }   

    void Particle::load() {
        //active = 1;
        //dead = false;
        shapePcl.Load();
        int r1 = rand() % 4;
        int r2 = rand() % 4;
        int r3 = rand() % 4;
		shapePcl.fillColor = glm::vec4(0.34f * r1, 0.34f * r2, 0.34f * r3, 1.0f);
        shapePcl.lineColor = glm::vec4(1.0f, 1.0f, 1.0f, 0.0f);
    }

    void Particle::update() {
        GLfloat t = (GLfloat)glfwGetTime();
        float v0 = 18;
        position.x = (v0 * cos(rad(80.0f)) * (t-birthTime) + pos0.x) * cos(rad(orientation));
        position.y = v0 * sin(rad(80.0f)) * (t-birthTime) - 0.5 * 9.81 * pow((t-birthTime), 2) + pos0.y;
        position.z = (v0 * cos(rad(80.0f)) * (t-birthTime) + pos0.x) * sin(rad(orientation));
        cout << "\n life : " << lifespan;
        if (position.y < 0.0) {
            dead = true;
            init(glm::vec3(0.0f, 0.0f, 0.0f),orientation);
        }
    }