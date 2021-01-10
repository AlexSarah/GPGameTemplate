#pragma once

#include "shapes.h"
#include "GameObject.h"	

class NewCube : public Shapes, public GameObject
{
public:

	NewCube();
	NewCube(string nature, int newId);
	NewCube(glm::vec3 translation, glm::vec3 rotation, glm::vec3 scale);
	NewCube(glm::vec3 mtranslation, glm::vec3 mrotation, glm::vec3 mscale, glm::vec4 mcolor);
	~NewCube();

private:
	Shapes			collisionP;
};

