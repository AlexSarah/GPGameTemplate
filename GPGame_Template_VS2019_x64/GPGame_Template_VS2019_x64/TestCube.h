#pragma once

#include "shapes.h"
#include "GameObject.h"	

class TestCube : public Shapes, public GameObject
{
public:

	TestCube();
	TestCube(string nature, int newId);
	TestCube(glm::vec3 translation, glm::vec3 rotation, glm::vec3 scale);
	TestCube(glm::vec3 mtranslation, glm::vec3 mrotation, glm::vec3 mscale, glm::vec4 mcolor);
	~TestCube();

private:
	Shapes			collisionP;
};

