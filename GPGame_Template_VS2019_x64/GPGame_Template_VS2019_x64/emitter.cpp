using namespace std;
#include "emitter.h";

void Emitter::create(int nb) {
	nbPcl = nb; 
	float o = 0.0;
	for (int i = 0; i < nbPcl; i++) {
		p[i].load();
		p[i].init(glm::vec3(0.0f, 0.0f, 0.0f), o);
		o += 1.0; // +1 degree
	}
}