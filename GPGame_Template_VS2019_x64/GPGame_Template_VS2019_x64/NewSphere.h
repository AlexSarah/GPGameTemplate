#pragma once

#pragma once

#include "shapes.h"
#include "GameObject.h"	

class NewSphere : public Shapes, public GameObject
{
public:

	NewSphere();
	NewSphere(string nature, int newId);
	NewSphere(glm::vec3 translation, glm::vec3 rotation, float radius);
	NewSphere(glm::vec3 mtranslation, glm::vec3 mrotation, float radius, glm::vec4 mcolor);
	NewSphere(glm::vec3 mtranslation, glm::vec3 mrotation, float radius, glm::vec4 mcolor, int mrotationSpeed);
	~NewSphere();

private:
	float rotationSpeed;
};

