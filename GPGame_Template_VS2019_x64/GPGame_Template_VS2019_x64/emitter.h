#pragma once
#include "particle.h"
class Emitter
{
public:
	Particle p[360];

	void create(int nb);

	int nbPcl;
};