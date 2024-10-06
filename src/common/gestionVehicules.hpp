#ifndef DEF_GESTIONVEHICULES_HPP
#define DEF_GESTIONVEHICULES_HPP
#include"car.h"
#include"objloader.hpp"
#include"decor.h"
#include"robot.hpp"
#include<GL/gl.h>
#include<GL/glu.h>
#include<C:\library\freeglut\include\GL\freeglut.h>


class gestionVehicules
{
    public:
    gestionVehicules();
    ~gestionVehicules();
    void init();
    void keyboard(unsigned char key, int x, int y);
    void keyboardUP(unsigned char key, int x, int y);
    void specialKey(int key, int x, int y);
    void specialKeyUP(int key, int x, int y);
    void update(std::vector<decor *> levels);
    void updatePhysics(float dt,std::vector<decor *> levels);
    void draw();
    void collisions();
    std::vector<vehicule*> v;
	void removeCloseVehicles( robot B, float threshold);
	void restoreVehiclesFarFrom(robot B, float threshold);

		
    private:
    std::vector<vehicule*>::iterator it;
    bool supprimer = false;
    std::vector<vehicule*> removedVehicles; // Liste des véhicules supprimés


};

#endif
