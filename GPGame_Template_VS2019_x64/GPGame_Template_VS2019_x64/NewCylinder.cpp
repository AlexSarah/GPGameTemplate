#include "NewCylinder.h"
#include <iostream>
#include <sstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

NewCylinder::NewCylinder()
{

	figure = Cube();
	figure.Load();

	figure_center(0);
	CollisionBoxP();

	//collision.fillColor = glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);
	collision.fillColor = glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);
	collision.lineColor = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
	type = 1;
	id = 42;
	subtype = 0;
}

NewCylinder::NewCylinder(string nature, int newId)
{
	figure = Sphere();
	figure.Load();

	figure_center(0);
	CollisionBoxP();

	//if (nature == "Cube")

	figure.fillColor = glm::vec4(0.7f, 0.7f, 0.7f, 1.0f);
	collision.lineColor = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);

	type = 1;
	id = newId;
	subtype = 0;
}

NewCylinder::NewCylinder(glm::vec3 mtranslation, glm::vec3 mrotation, float radius)
{
	figure = Sphere();
	figure.Load();

	figure_center(0);
	CollisionBoxP();

	translation = mtranslation;
	rotation = mrotation;
	if (radius > 1.0)
		scaling = scaling = glm::vec3(radius, radius, radius);

	collision.fillColor = glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);
	type = 1;
	id = 500;
	subtype = 0;

}



NewCylinder::NewCylinder(glm::vec3 mtranslation, glm::vec3 mrotation, float radius, float height,  glm::vec4 mcolor)
{
	figure = Sphere();
	figure.Load();

	figure_center(0);
	CollisionBoxP();

	translation = mtranslation;
	rotation = mrotation;
	if (radius > 1.0 && height > 1.0)
		scaling = scaling = glm::vec3(radius, height, radius);
	figure.fillColor = mcolor;

}


NewCylinder::NewCylinder(glm::vec3 mtranslation, glm::vec3 mrotation, float radius, float height,  glm::vec4 mcolor, int mrotationSpeed)
{
	figure = Sphere();
	figure.Load();

	figure_center(0);
	CollisionBoxP();

	translation = mtranslation;
	rotation = mrotation;
	if (radius > 1.0 && height > 1.0)
		scaling = scaling = glm::vec3(radius, height, radius);
	figure.fillColor = mcolor;
	rotationSpeed = mrotationSpeed;
}


NewCylinder::~NewCylinder() {

}