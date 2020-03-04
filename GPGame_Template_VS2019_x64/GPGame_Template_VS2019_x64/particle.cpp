#include "particle.h"
#include <iostream>
using namespace std;
#include "shapes.h"
#include "graphics.h"
#include <glm\gtx\transform.hpp>
#include "emitter.h"
#define rad glm::radians

    //Default Constructor 
    Particle::Particle()
    {
        id = -1;
        lifespan = 0;
        dead = true;
        collision = false;
        birthTime = 0;
    }

    void Particle::init(glm::vec3 vec,float o, Shapes shape) {
        pos0 = glm::vec3(vec.x,vec.y,vec.z);
        position = glm::vec3(pos0.x, pos0.y, pos0.z);
        orientation = o;
        shapePcl = shape;
    }   

    /*void Particle::update() {
        GLfloat t = (GLfloat)glfwGetTime();
        float v0 = 10;
        position.x = (v0 * cos(rad(80.0f)) * (t-birthTime) + pos0.x) * cos(rad(orientation));
        position.y = v0 * sin(rad(80.0f)) * (t-birthTime) - 0.5 * 9.81 * pow((t-birthTime), 2) + pos0.y;
        position.z = (v0 * cos(rad(80.0f)) * (t-birthTime) + pos0.x) * sin(rad(orientation));
        if (position.y < 0.0) {
            dead = true;
            init(glm::vec3(0.0f, 0.0f, 0.0f),orientation,shapePcl);
        }
    }*/

    void Particle::updatePosPcl(float angle, double v0) {
        GLfloat t = (GLfloat)glfwGetTime();
        position.x = (v0 * cos(rad(angle)) * (t - birthTime) + pos0.x) * cos(rad(orientation));
        position.y = v0 * sin(rad(angle)) * (t - birthTime) - 0.5 * 9.81 * pow((t - birthTime), 2) + pos0.y;
        position.z = (v0 * cos(rad(angle)) * (t - birthTime) + pos0.x) * sin(rad(orientation));
        lifespan += 1;
        if (position.y < 0.0) {
            //dead = true;
            //init(glm::vec3(0.0f, 0.0f, 0.0f), orientation, shapePcl);
        }
    }

    void Particle::updateFountain() {
        GLfloat currentTime = (GLfloat)glfwGetTime();
        if (dead == true) {
            int r = rand() % 15;
            if (r == 0) {
                dead = false;
                birthTime = currentTime;
            }
        }
        if (dead == false) {
            updatePosPcl(80.0f, 8);
        }
    }

    void Particle::updateShooting() {
        GLfloat currentTime = (GLfloat)glfwGetTime();
        if (dead == true) {
            int r = rand() % 15;
            if (r == 0) {
                dead = false;
                birthTime = currentTime;
            }
        }
        if (dead == false) {
            updatePosPcl(80.0f, 8);
        }
    }

    void Particle::updateAfterCollision(bool touched) {
        /*if (lifespan > 20 && touched) {
            collision = true;
        }
        if (collision) {
            position = glm::vec3(position.x, position.y * (-0.75), position.z);
         }*/
    }

    /*void updateOnePcl(double v0) {
        GLfloat t = (GLfloat)glfwGetTime();
        position.x = (v0 * cos(rad(angle)) * (t - birthTime) + pos0.x) * cos(rad(orientation));
        position.y = v0 * sin(rad(angle)) * (t - birthTime) - 0.5 * 9.81 * pow((t - birthTime), 2) + pos0.y;
        position.z = (v0 * cos(rad(angle)) * (t - birthTime) + pos0.x) * sin(rad(orientation));
    }*/

    /*void Particle::updateCrowdPcl(float angle, double v0) {
        GLfloat t = (GLfloat)glfwGetTime();
        position.x = (v0 * cos(rad(angle)) * (t - birthTime) + pos0.x) * cos(rad(orientation));
        position.y = v0 * sin(rad(angle)) * (t - birthTime) - 0.5 * 9.81 * pow((t - birthTime), 2) + pos0.y;
        position.z = (v0 * cos(rad(angle)) * (t - birthTime) + pos0.x) * sin(rad(orientation));
        if (position.y < 0.0) {
            dead = true;
            init(glm::vec3(0.0f, 0.0f, 0.0f), orientation, shapePcl);
        }
    }*/

    void Particle::setColor() {
        int r1 = rand() % 4;
        int r2 = rand() % 4;
        int r3 = rand() % 4;
        shapePcl.fillColor = glm::vec4(0.34f * r1, 0.34f * r2, 0.34f * r3, 1.0f);
        shapePcl.lineColor = glm::vec4(1.0f, 1.0f, 1.0f, 0.0f);
    }