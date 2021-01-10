#pragma once

#include "shapes.h"
#include "GameObject.h"


class NewCylinder : public Shapes, public GameObject
{
public:

	NewCylinder();
	NewCylinder(string nature, int newId);
	NewCylinder(glm::vec3 translation, glm::vec3 rotation, float radius);
	NewCylinder(glm::vec3 mtranslation, glm::vec3 mrotation, float radius, float height, glm::vec4 mcolor);
	NewCylinder(glm::vec3 mtranslation, glm::vec3 mrotation, float radius, float height,  glm::vec4 mcolor, int mrotationSpeed);
	~NewCylinder();

private:
	float rotationSpeed;
};

