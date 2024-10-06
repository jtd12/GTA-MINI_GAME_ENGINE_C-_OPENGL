#ifndef DEF_PARTICULE_HPP
#define DEF_PARTICULE_HPP
#define MAX_PARTICLES 700  // Number of particles
#include <math.h>
#include <stdlib.h>
#include<C:\library\freeglut\include\GL\freeglut.h>
#include"vector.h"

class particules
{
	
typedef struct {
    float position[3];  // Particle position
    float velocity[3];  // Particle velocity
    float color[4];     // RGBA color
    float life;         // Particle lifetime
    float size;         // Size of the particle
} Particle;


public:
	particules();
	void initParticle(Particle* p, vector3d posCar);
	void updateParticles(float deltaTime,vector3d posCar,bool brake,bool right,bool left);
	void renderParticles();
	void setLife();
	Particle particles[MAX_PARTICLES];
	
};
#endif
