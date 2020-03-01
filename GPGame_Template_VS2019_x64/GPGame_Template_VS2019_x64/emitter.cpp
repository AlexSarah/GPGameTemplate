using namespace std;
#include "emitter.h";

void Emitter::create() {
	float t = 0;
	for (int i = 0; i < 10; i++) {
		p[i].load();
		p[i].vec0.x = -2.0f+t;
		p[i].vec0.y = 5.5f;
		p[i].vec0.z = 0.0f;
		//p[i].init(glm::vec3(-2.0f + t, 5.5f, 0.0f));
		t += 1.0;
	}
}