#include"particule.hpp"

 particules::particules()
{
	 
}
 


// Function to initialize a particle
void particules::initParticle(Particle* p, vector3d posCar) {
    // Initial position at car exhaust (e.g., at (0, 0, 0) or relative to the car's rear)
    p->position[0] = posCar.x-80;
    p->position[1] = posCar.y-20;
    p->position[2] = posCar.z-7;

    // Give the particle a random upward velocity
    p->velocity[0] = (float)(rand() % 70 - 25) / 1.0f; // X velocity
    p->velocity[1] = (float)(rand() % 50) / 10.0f;      // Y velocity (upward)
    p->velocity[2] = (float)(rand() % 50 - 25) / 100.0f; // Z velocity

    // Random color, starting with a dark gray and fading
    p->color[0] = 0.5f;
    p->color[1] = 0.5f;
    p->color[2] = 0.5f;
    p->color[3] = 1.0f;  // Alpha (fully opaque)

    // Initial lifetime (how long the particle exists)
    p->life = 2.0f;  // Starts at full life

    // Set size
    p->size = 0.7f;
}

// Function to update particles
void particules::updateParticles(float deltaTime,vector3d posCar,bool brake,bool right,bool left) {
    for (int i = 0; i < MAX_PARTICLES; i++) {
       
            // Update position based on velocity and deltaTime
            particles[i].position[0] += particles[i].velocity[0] * deltaTime;
            particles[i].position[1] += particles[i].velocity[1] * deltaTime;
            particles[i].position[2] += particles[i].velocity[2] * deltaTime;

            // Fade out by decreasing alpha
            particles[i].color[3] -= 0.01f * deltaTime;

            // Reduce the lifetime of the particle
            particles[i].life -= 0.1f * deltaTime;
            
            

            // Reduce the size as it fades
            particles[i].size += 0.002f * deltaTime;
       
        
        if(particles[i].life<-0.01f && brake)
        {
        	
        	particles[i].life=2;
        	particles[i].position[0] = posCar.x-80;
		    particles[i].position[1] = posCar.y-12;
		    particles[i].position[2] = posCar.z-5;
		    particles[i].velocity[0] = (float)(rand() % 50 -20 ) / 1.0f; // X velocity
		    particles[i].velocity[1] = (float)(rand() % 50) / 10.0f;      // Y velocity (upward)
		    particles[i].velocity[2] = (float)(rand() % 50 - 25) / 100.0f; // Z velocity
		}
          
            // Respawn the particle
        
        }

}


// Function to render particles
void particules::renderParticles() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  // Enable transparency

    for (int i = 0; i < MAX_PARTICLES; i++) {
        if (particles[i].life > 0.0f) {
            // Set the color (with transparency)
            glColor4fv(particles[i].color);

            // Draw each particle as a point or small quad
            glPushMatrix();
            glTranslatef(particles[i].position[0], particles[i].position[1], particles[i].position[2]);

            // Draw as a quad (or use a point if you prefer)
            glBegin(GL_QUADS);
                glVertex3f(-particles[i].size, -particles[i].size, 0.0f);
                glVertex3f( particles[i].size, -particles[i].size, 0.0f);
                glVertex3f( particles[i].size,  particles[i].size, 0.0f);
                glVertex3f(-particles[i].size,  particles[i].size, 0.0f);
            glEnd();

            glPopMatrix();
        }
    }

    glDisable(GL_BLEND);  // Disable transparency
}
