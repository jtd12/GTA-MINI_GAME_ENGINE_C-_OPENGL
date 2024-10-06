#include"gameSetup.hpp"

setup::setup()
{
	obj=new objloader();
	
	std::vector<collisionplane> mapcp;
	std::vector<collisionplane> mapcp2;
	std::vector<vector3d> mapsp;
	mapsp.push_back(vector3d(0.1,0.2,0.1));
	
	unsigned int map=obj->load("data/decor.obj",NULL);
	unsigned int mapCollision=obj->load("data/collision.obj",&mapcp);
	unsigned int map2=obj->load(" ",NULL);
	unsigned int mapCollisionMurs=obj->load("data/collision2.obj",&mapcp2);
	
	levels.push_back(new decor("name",map,mapcp,mapsp));
	levels.push_back(new decor("name",mapCollision,mapcp,mapsp));
	levels.push_back(new decor("name",map2,mapcp,mapsp));
	levels.push_back(new decor("name",mapCollisionMurs,mapcp2,mapsp));
	
	gestion=new gestionVehicules();
	sky=new skybox();
	cam=new camera();
	rb=new robot(collisionsphere(vector3d(-70,15.0,0),8.0f));


	for(int i=0;i<4;i++)
	 water.push_back(new ocean());
	 
	for(int i=0;i<water.size();i++)
	 water[i]->loadTexture("data/water.bmp");
	 
	 
	 blur=new blurMotion();
	 
}



setup::~setup()
{
delete gestion;
delete sky;
delete cam;
delete rb;
for(int i=0;i<levels.size();i++)
 delete levels[i];
delete obj;
for(int i=0;i<water.size();i++)
 delete water[i];
delete blur;
 
}

void setup::mouseMove(int mx,int my)
{

		cam->control(mx,my);
		
}




void setup:: mouseState(int button, int state, int x, int y)
{
	cam->mouse( button,  state,  x,  y);
}
void setup::keyboard(unsigned char key, int x, int y)
{
 gestion->keyboard(key,x,y);
 rb->keyboard(key, x,y);
 
}

void setup::keyboardUP(unsigned char key, int x, int y)
{
	 rb->keyboardUP(key, x,y);
	 gestion->keyboardUP(key,x,y);
}

void setup::specialKey(int key, int x, int y)
{
		rb->handleKeyPress(key,x,y);
		gestion->specialKey(key,x,y);

}
void setup::specialKeyUP(int key, int x, int y)
{
		gestion->specialKeyUP(key,x,y);
		rb->handleKeyPressUP(key,x,y);
}

void setup::update()
{
	gestion->update(levels);
	gestion->collisions();
	rb->collisions(rb,gestion->v[0],levels[3]->getCollisionPlanes());
	rb->updateCollision(levels[1]->getCollisionPlanes());
	rb->updateCollisionMurs(levels[3]->getCollisionPlanes(),rb,gestion->v[0]);
	sky->update();
	

 	gestion->v[0]->update(rb->getExit(),blur);
	rb->entrerVehicule(gestion->v[0]);
	
	
 	gestion->removeCloseVehicles(*rb,150);
 	gestion->restoreVehiclesFarFrom(*rb,150);

}

void setup::timer(int value) {
    float dt = 0.016f; // Time step (16ms for ~60 FPS)
    gestion->updatePhysics(dt,levels);
    
	rb->updateMovement(dt,gestion->v[0]->getControl(),blur);
	 
	for(int i=0;i<water.size();i++)
     water[i]->update(dt);

}


void setup::hud()
{
	
	glPushMatrix();
	glTranslated(-0.0,-0.0,-0.0);
	glScaled(1.0,1.0,0);
	blur->blurGlowTexture();
	glPopMatrix();



	
}


void setup::drawHud()
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0,0,1,0);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	hud();	
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	
}


void setup::draw(int w,int h)
{
	glTranslated(0,-10,-50);
	
	
	if(gestion->v[0]->getControl()==false)
	  cam->update(rb->getLocation());
	else
	     cam->update(gestion->v[0]->getLocation());

	glPushMatrix();
	glRotated(sky->getRot(),0,0.5,0);
	sky->drawSkybox(20000);
	glPopMatrix();
	glPushMatrix();
	for(int i=0;i<levels.size();i++)
 	 levels[i]->draw();
	glPopMatrix();
	glPushMatrix();
	gestion->draw();
	glPopMatrix();

	glPushMatrix();
	rb->drawRobot(gestion->v[0]);
	glPopMatrix();
	
	glPushMatrix();
	glTranslated(0,-70,-1010);
	glScaled(4,1,4);
	water[0]->draw();
	glPopMatrix();
	glPushMatrix();
	glTranslated(-1010,-70,0);
	glScaled(4,1,4);
	water[1]->draw();
	glPopMatrix();
	glPushMatrix();
	glTranslated(0,-70,0);
	glScaled(4,1,4);
	water[2]->draw();
	glPopMatrix();
	glPushMatrix();
	glTranslated(-1010,-70,-1010);
	glScaled(4,1,4);
	water[3]->draw();
	glPopMatrix();
	
	blur->copySceneToTexture(w,h);
	drawHud();


}

void setup::reshapeTextures(int w,int h)
{
	blur->initializeTexture(w,h);
}
