#include "TestCube.h"
#include <iostream>
#include <sstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

NewCube::NewCube()
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

NewCube::NewCube(string nature, int newId) 
{
	figure = Cube();
	figure.Load();

	figure_center(0);
	CollisionBoxP();

	//if (nature == "Cube")
		
	figure.fillColor = glm::vec4(0.7f, 0.7f, 0.7f, 1.0f);
	//collision.fillColor = glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);
	//collision.lineColor = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);

	if (nature == "Wall")
	{
		scaling = glm::vec3(1.0f, 2.0f, 0.4f);
		subtype = 1;
	}
	else if (nature == "Ground")
	{
		scaling = glm::vec3(1000.0f, 0.001f, 1000.0f);
		subtype = 2;
	}

	type = 1;
	id = newId;
	subtype = 0;
}

NewCube::NewCube(glm::vec3 mtranslation, glm::vec3 mrotation, glm::vec3 mscale)
{
	figure = Cube();
	figure.Load();

	figure_center(0);
	CollisionBoxP();

	translation = mtranslation;
	rotation = mrotation;
	scaling = mscale;

	collision.fillColor = glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);
	type = 1;
	id = 500;
	subtype = 0;

}



NewCube::NewCube(glm::vec3 mtranslation, glm::vec3 mrotation, glm::vec3 mscale, glm::vec4 mcolor) 
{
	figure = Cube();
	figure.Load();

	figure_center(0);
	CollisionBoxP();

	translation = mtranslation;
	rotation = mrotation;
	scaling = mscale;
	color = mcolor;
	figure.fillColor = color;

}



NewCube::~NewCube() {

}