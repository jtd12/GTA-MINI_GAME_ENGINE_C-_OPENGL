#include"gestionVehicules.hpp"


gestionVehicules::gestionVehicules()
{
	init();

}

gestionVehicules::~gestionVehicules()
{

for(int i=0;i<v.size();i++)
 delete v[i];

}

void gestionVehicules::init()
{
v.push_back(new vehicule(collisionsphere(vector3d(40,12.0,0),12.0f),vector3d(1.25f,1.25f,1.25f),"data/vehicule/camionnete.obj",true));

for(int i=0;i<10;i++)
v.push_back(new vehicule(collisionsphere(vector3d(350+(i*250),12.0,0),10.0f),vector3d(0.5f,0.5f,0.5f),"data/vehicule/vehicule0.obj",false));

for(int i=0;i<10;i++)
v.push_back(new vehicule(collisionsphere(vector3d(250+(i*250),12.0,150),10.0f),vector3d(0.5f,0.5f,0.5f),"data/vehicule/vehicule1.obj",false));

}


void gestionVehicules::removeCloseVehicles( robot B, float threshold) {
    // Utiliser un itérateur pour parcourir la liste et supprimer les éléments
    for (it = v.begin(); it != v.end(); ) {
        if ((*it)->isCloseTo(B.getLocation(),threshold)) {
        	
        
        	  removedVehicles.push_back(*it);
            // Supprimer l'objet et libérer la mémoire
              it = v.erase(it); // Supprimer de la liste principale
        
  
            } else {
                    ++it; // Passer à l'élément suivant
                }
            } 
	

}

 void gestionVehicules::restoreVehiclesFarFrom(robot B, float threshold) {
        for ( it = removedVehicles.begin(); it != removedVehicles.end(); ) {
            if (!(*it)->isCloseTo(B.getLocation(), threshold)) {
                // Déplacer le véhicule vers la liste principale
                v.push_back(*it);
                it = removedVehicles.erase(it); // Supprimer de la liste des véhicules supprimés
            } else {
                ++it; // Passer à l'élément suivant
            }
        }
    }



void gestionVehicules::keyboard(unsigned char key, int x, int y)
{

for(int i=0;i<v.size();i++)
 v[i]->keyboard(key,x,y);
}

void gestionVehicules::keyboardUP(unsigned char key, int x, int y)
{

for(int i=0;i<v.size();i++)
 v[i]->keyboardUP(key,x,y);
}

void gestionVehicules::specialKey(int key, int x, int y)
{

for(int i=0;i<v.size();i++)
 v[i]->handleKeyPress(key,x,y);
}

void gestionVehicules::specialKeyUP(int key, int x, int y)
{

for(int i=0;i<v.size();i++)
 v[i]->handleKeyPressUP(key,x,y);
}


void gestionVehicules::collisions()
{
	  for(int i=0;i<v.size();i++)
  		v[i]->collisions(v);
}
void gestionVehicules::update(std::vector<decor *> levels)
{

    for(int i=0;i<v.size();i++)
    {
	v[i]->updateCollision(levels[1]->getCollisionPlanes());
	v[i]->updateCollisionMurs(levels[3]->getCollisionPlanes());
    }
}

void gestionVehicules::updatePhysics(float dt,std::vector<decor *> levels)
{
   for(int i=0;i<v.size();i++)
     v[i]->updatePhysics(dt,levels[1]->getCollisionPlanes(),levels[3]->getCollisionPlanes());
    
}

void gestionVehicules::draw()
{
	
   
   for(int i=0;i<v.size();i++)
   {
    glPushMatrix();
    v[i]->draw();
    glPopMatrix();
}

  
    
}
