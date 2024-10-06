#include"car.h"

roue::roue(const char * filename)
{
		obj=new objloader();
		roue_=obj->load(filename,NULL);
 		suspensionRestLength = 0.5f;
        suspensionCurrentLength = suspensionRestLength;
        springConstant = 10000.0f;
        dampingConstant = 1000.0f;
        position = vector3d(0.0f, 0.0f, 0.0f);
}

 void roue::updateSuspension(float verticalForce, float dt) {
        float compression = suspensionRestLength - suspensionCurrentLength;
        float springForce = -springConstant * compression;
        float dampingForce = -dampingConstant * (compression / dt);
        float suspensionForce = springForce + dampingForce + verticalForce;
        suspensionCurrentLength += suspensionForce * dt;
        suspensionCurrentLength = fmax(0.1f, fmin(suspensionRestLength, suspensionCurrentLength));
    }

roue::~roue()
{
	delete obj;
}
void roue::update()
{
	
}
vector3d roue::getLocation()
{
	return loc;
}
void roue::setLocation(vector3d vec)
{
	loc.x=vec.x;
	loc.y=vec.y;
	loc.z=vec.z;
}
void roue::draw()
{
	glPushMatrix();
	glTranslated(position.x,position.y,position.z);
	glCallList(roue_);
	glPopMatrix();
}

tb::tb(const char * filename)
{
	obj=new objloader();
	tb_=obj->load(filename,NULL);
}
tb::~tb()
{
	delete obj;
}
void tb::update()
{
	
}
void tb::draw()
{
	glPushMatrix();
	glCallList(tb_);
	glPopMatrix();
}


porte_vitre::porte_vitre(const char * filename)
{
	obj=new objloader();
	porte_vitre_=obj->load(filename,NULL);
}
porte_vitre::~porte_vitre()
{
	delete obj;
}
void porte_vitre::update()
{
	
}
void porte_vitre::draw()
{
		glPushMatrix();
		glEnable(GL_COLOR_MATERIAL);
		glEnable(GL_BLEND) ;
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) ; 
		glCallList(porte_vitre_);
		glDisable(GL_BLEND) ;
		glDisable(GL_COLOR_MATERIAL);
		glPopMatrix();
}
void porte::setRotPorte(float r)
{
	rotPorte+=r;
}
void porte::setRotPorteEgal(float r)
{
	rotPorte=r;
}
float porte::getRotPorte()
{
	return rotPorte;
}
porte::porte(const char * filename)
{
	obj=new objloader();
	rotPorte=0.0f;
	p1_vitre=new porte_vitre("data/camionnete_vitres_porte1.obj");
	p2_vitre=new porte_vitre("data/camionnete_porte2_vitres.obj");
	porte_=obj->load(filename,NULL);
}
porte::~porte()
{
	delete obj;
	delete 	p1_vitre;
	delete 	p2_vitre;
}
void porte::update()
{
	p1_vitre->update();
	p2_vitre->update();
}
void porte::draw()
{
		glPushMatrix();
		p1_vitre->draw();
		p2_vitre->draw();
		glCallList(porte_);
		glPopMatrix();
}

vitres::vitres()
{
	obj=new objloader();
	vitres_=obj->load("data/camionnete_vitres.obj",NULL);
}
vitres::~vitres()
{
	delete obj;
}

void vitres::update()
{
	
}
void vitres::draw()
{
	glPushMatrix();
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_BLEND) ;
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) ; 
	glCallList(vitres_);
	glDisable(GL_BLEND) ;
	glDisable(GL_COLOR_MATERIAL);
	glPopMatrix();
}


volant::volant()
{
	obj=new objloader();
	volant_=obj->load("data/volant.obj",NULL);
}
volant::~volant()
{
	delete obj;
}

void volant::update()
{
	
}

void volant::draw()
{
	glPushMatrix();
	glTranslated(-3,0,-4.95);
	glCallList(volant_);
	glPopMatrix();
}




boundingboxCar::boundingboxCar(vector3d loc)
{
	pos=loc;
	
}
		boundingboxCar::~boundingboxCar()
		{
			
		}
		
	
		void boundingboxCar::drawCollision()
		{
			glPushMatrix();
			glTranslated(pos.x,pos.y,pos.z);
		//	glutSolidCube(20.0f);
			glPopMatrix();
		}
		vector3d boundingboxCar::getLocation()
		{
			return pos;
		}
		void boundingboxCar::setLocation(vector3d loc)
		{
			pos=loc;
		}
		
vehicule::vehicule(collisionsphere ccs,vector3d s,const char * filename,bool visible)
{
	
	obj=new objloader();	
	car=obj->load(filename,NULL);
	scale=s;
	
	for(int i=0;i<4;i++)
	 wheel.push_back(new roue("data/camionnete_roue.obj"));

	v=new vitres();
	door.push_back(new porte("data/camionnete_porte1.obj"));
	door.push_back(new porte("data/camionnete_porte2.obj"));
	tab=new tb("data/camionnete_tb.obj");
	vv=new volant();
    groundLevel = -3.0f;
	carSpeed = 0.15f;     // Speed of the car movement
	carRotation = 0.0f;    // Rotation angle of the car around the Y axis
    carTurnSpeed = 0.5f;
    gravity = 9.81f;
    wheel[0]->setLocation(vector3d(2,cs.center.y-15,5));
    wheel[1]->setLocation(vector3d(-10,cs.center.y-15,5));
    wheel[2]->setLocation(vector3d(2,cs.center.y-15,-5));
    wheel[3]->setLocation(vector3d(-10,cs.center.y-15,-5));
	deltaTime = 0.016f; // Assuming 60 FPS
	up=false;
	down=false;
	right=false;
	left=false;
	cs=ccs;
	vx=0;
	vz=-1.0;
	direction=0.0f;
	speed=0.0;
	steeringAngle=0.0;
	wheelDistance=200.0;
	force.change(0.0,-0.2f,0.0);
	setPosition(vector3d(cs.center));
	isground=false;
	modeAvancer=false;
	modeReculer=false;
	pitchAngle=0.0f;
	rollAngle=0.0f;
	control=false;
	isVisible=visible;
	bb.push_back(new boundingboxCar(vector3d(-30,1.0,0)));
	bb.push_back(new boundingboxCar(vector3d(30,1.0,0)));
	regularSpeed=1.0f;
  
              part.push_back(particules());  // Si aucun système n'est créé, en créer un
            
            
            
		
	  for (int i = 0; i < MAX_PARTICLES; i++) {
     
            // Initier une nouvelle particule
            part[0].initParticle(&part[0].particles[i], getLocation());
        }
    
    
 }

vehicule::~vehicule()
{
	delete obj;
	delete v;
	delete vv;

	for(int i=0;i<bb.size();i++)
	 delete bb[i];
	for(int i=0;i<door.size();i++)
	  delete door[i];
	delete tab;
	for(int i=0;i<wheel.size();i++)
	 delete wheel[i];

}

vector3d vehicule::getScale()
{
	return scale;
}

void vehicule:: updatePhysics(float dt,std::vector<collisionplane>& collplane,std::vector<collisionplane>& collplane2) {
	
	  acceleration = -brakingForce / CAR_MASS;
    speed += acceleration * dt;

    // Stop the car if speed drops below zero
    if (speed < 0.0f) {
        speed = 0.0f;
        acceleration = 0.0f;
    }
    if(control)
	{

    
    	 vx = speed * cos(direction);
         vz = -speed * sin(direction);
    
    if(modeAvancer)
	{
	    cs.center.x += vx * dt*regularSpeed;
	    cs.center.z += vz * dt*regularSpeed;
	    
	    
	    		for(int i=0;i<collplane2.size();i++)
			{
			vector3d newPos(getLocation()+bb[1]->getLocation());
				if(collision::sphereplane(newPos,collplane2[i].normal,collplane2[i].p[0],collplane2[i].p[1],collplane2[i].p[2],collplane2[i].p[3],cs.r)==false)
				{
					regularSpeed=1.0f;
				
		
	}
}

	}
	
	if(modeReculer)
	{
			cs.center.x -= vx * dt*regularSpeed;
	    cs.center.z -= vz * dt*regularSpeed;
	    
			for(int i=0;i<collplane2.size();i++)
			{
			vector3d newPos(getLocation()+bb[0]->getLocation());
				if(collision::sphereplane(newPos,collplane2[i].normal,collplane2[i].p[0],collplane2[i].p[1],collplane2[i].p[2],collplane2[i].p[3],cs.r)==false)
				{
					regularSpeed=1.0f;
				
		
	}
}
	}
}

	float frontLoadIncrease = brakingForce / 2.0f;  // Apply extra load on front wheels
    float rearLoadDecrease = brakingForce / 2.0f;   // Reduce load on rear wheels
    // Simple suspension model
    for (int i = 0; i < 4; i++) {
    	
    	  float suspensionLoad = (i < 2) ? frontLoadIncrease : -rearLoadDecrease;  // Front vs. rear
        
        
    float displacement = suspensionHeight[i] - SUSPENSION_TRAVEL;

    // Calculate spring force
    float springForce = -SPRING_CONSTANT *  displacement;
    // Calculate damping force
    float dampingForce = -DAMPING_COEFFICIENT * suspensionVelocity[i];
    
    
  float totalForce = springForce + dampingForce + suspensionLoad;
    // Update suspension height
       suspensionVelocity[i] += (totalForce / (CAR_MASS / 4)) *dt;
        suspensionHeight[i] += suspensionVelocity[i] * dt;
        
        if (suspensionHeight[i] > REST_SUSPENSION_HEIGHT) suspensionHeight[i] = REST_SUSPENSION_HEIGHT;
        if (suspensionHeight[i] < 0.0f) suspensionHeight[i] = 0.0f;
        
    }
    for(int i=0;i<collplane.size();i++)
				if(collision::sphereplane(cs.center,collplane[i].normal,collplane[i].p[0],collplane[i].p[1],collplane[i].p[2],collplane[i].p[3],cs.r))
				{
pitchAngle = (suspensionHeight[0]-suspensionHeight[2]) * 40.0f;  // Left-to-right tilt
rollAngle = (suspensionHeight[1]-suspensionHeight[3]) * 30.0f; // Front-to-back tilt

direction += steeringAngle * dt;
	}
}

bool vehicule::collisionAABB( vehicule& v1, vehicule& v2) {
    return (v1.getLocation().x < v2.getLocation().x + v2.scale.x+10 &&
            v1.getLocation().x + v1.scale.x+30 > v2.getLocation().x &&
            v1.getLocation().z < v2.getLocation().z + v2.scale.z+30 &&
            v1.getLocation().z + v1.scale.z+30 > v2.getLocation().z);
}

void vehicule::collisions(std::vector<vehicule*> cc)
{
	 for (int i = 0; i < cc.size(); i++) {
        for (int j = i + 1; j < cc.size(); j++) {
            if (collisionAABB(*cc[i], *cc[j])) {
            	 cc[i]-> regularSpeed=-12.0f;
            	 cc[j]-> regularSpeed=-12.0f;
            	 cc[i]-> speed-=0.1f;
  				 cc[j]-> speed-=0.1f;
 
            }
        }
        
    }
}


/*
  float vehicule::distance(robot& other)
{
	return sqrt(((getLocation().x - other.getLocation().x) * (getLocation().x - other.getLocation().x)) + ((getLocation().y - other.getLocation().y) * (getLocation().y - other.getLocation().y)) + ((getLocation().z - other.getLocation().z) * (getLocation().z - other.getLocation().z)));
}
*/
     bool vehicule::isCloseTo( vector3d other,float threshold) {
        return (vecteur.distance(other,getLocation()) > threshold);
    }
    
 vector3d vehicule::getLocation()
  {
  	return cs.center;
  }
  
  void vehicule::setLocation(vector3d location)
{
	cs.center.change(location);
}

  void vehicule::setPosition(vector3d pos)
   {
  cs.center=pos;
  setLocation(pos);
   }
  
  float vehicule::getRotation()
  {
  	return direction;
  }


	bool vehicule::getControl()
	{
		return control;
	}

	void vehicule::setControl(bool c)
	{
		control=c;
	}
	

float vehicule::getSpeed()
{
	return speed;
}

bool vehicule::getAvancer()
{
	return modeAvancer;
}

bool vehicule::getReculer()
{
	return modeReculer;
}

void vehicule::updateCollisionMurs(std::vector<collisionplane>& collplane)
{
	vector3d newPos(getLocation()+bb[0]->getLocation());
			for(int i=0;i<collplane.size();i++)
			{
			
				if(collision::sphereplane(newPos,collplane[i].normal,collplane[i].p[0],collplane[i].p[1],collplane[i].p[2],collplane[i].p[3],cs.r))
				{
			regularSpeed=-15.0f;
			speed-=0.1f;
		
			
				}
				
			
				
			
			}
			
				vector3d newPos2(getLocation()+bb[1]->getLocation());
			for(int i=0;i<collplane.size();i++)
			{
			
				if(collision::sphereplane(newPos2,collplane[i].normal,collplane[i].p[0],collplane[i].p[1],collplane[i].p[2],collplane[i].p[3],cs.r))
				{
			regularSpeed=-15.0f;
			speed-=0.1f;
		
			
				}
				
			
				
			
			}
	
		
			

}

void vehicule::update(bool exit,blurMotion* motionBB)
{
	float deltaTime = 0.1f;  // Assume a fixed time step for simplicity


	for(int i=0;i<1;i++)
    part[i].updateParticles(deltaTime, getLocation(),space,right,left);  // Mettre à jour les particules


 
	v->update();
	vv->update();
	for(int i=0;i<door.size();i++)
	 door[i]->update();
	tab->update();
	for(int i=0;i<wheel.size();i++)
	 wheel[i]->update();
	 
if(control)
{
	
if(modeAvancer)
{
if(up)
{

		motionBB->update(2000);
speed += ACCELERATION;
            if (speed > MAX_SPEED) speed = MAX_SPEED;
            
        
}
}
if(up)

if(modeReculer)
{
if(up)
{
		motionBB->update(2000);
speed += ACCELERATION;
            if (speed > MAX_SPEED) speed = MAX_SPEED;
}

	
}

if(space)
{
	
	
    
}

if(space || exit)
{
  motionBB->update(-800);
  brakingForce = MAX_BRAKING_FORCE;
  speed-=brakingForce;

}
 else if(space==false)
{
 brakingForce = 0.0;
}

if(up)
{
if(right)
{
	
	steeringAngle = -STEERING_ANGLE_MAX;
        
}

else if( left)
{
	
	steeringAngle = STEERING_ANGLE_MAX;

}
else
{
	steeringAngle = 0.0f;
}

}
else{
	steeringAngle = 0.0f;
}
}

}

void vehicule::ouvrirPorte1()
{
	door[0]->setRotPorte(-0.5f);
	if(door[0]->getRotPorte()<-75.0f)
	{
		door[0]->setRotPorteEgal(-75.0f);
	}
}

void vehicule::fermerPorte1()
{
	door[0]->setRotPorte(0.5f);
		if(door[0]->getRotPorte()<0.0f)
	{
		door[0]->setRotPorteEgal(0.0f);
	}

}

void vehicule::ouvrirPorte2()
{
	door[1]->setRotPorte(0.5f);
	if(door[1]->getRotPorte()>75.0f)
	{
		door[1]->setRotPorteEgal(75.0f);
	}
}

void vehicule::fermerPorte2()
{
	door[1]->setRotPorte(-0.5f);
		if(door[1]->getRotPorte()>0.0f)
	{
		door[1]->setRotPorteEgal(0.0f);
	}

}

void vehicule::updateCollision(std::vector<collisionplane>& collplane)
{
	if(dir.y>=force.y)
			dir+=force;
			
			vector3d newPos(getLocation());
			newPos+=dir;
		
	
			for(int i=0;i<collplane.size();i++)
				if(collision::sphereplane(newPos,collplane[i].normal,collplane[i].p[0],collplane[i].p[1],collplane[i].p[2],collplane[i].p[3],cs.r))
				{
					
				}
				
				
				 if(getLocation().y<newPos.y)
				  isground=true;
				  else
				   isground=false;
		    
				setPosition(newPos);
}



void vehicule::draw()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glTranslatef(cs.center.x, (suspensionHeight[0] - suspensionHeight[2])+cs.center.y, cs.center.z);
	glRotatef(pitchAngle, 1.0f, 0.0f, 0.0f);  // Pitch (tilt forward/backward)
    glRotatef(rollAngle, 0.0f, 0.0f, 1.0f);   // Roll (tilt side-to-side)	
	glRotatef(direction * 180.0f / M_PI, 0.0f, 1.0f, 0.0f);
	glScaled(scale.x,scale.y,scale.z);
	glColor3f(1.0f, 0.8f, 0.0f);  // Bright yellow for glow
  	glCallList(car);
  	if(isVisible)
	  elementCars();
	if(isVisible==false)
	  elementOtherCars();
	
}

void vehicule::elementCars()
{
	glPushMatrix();
	for(int i=0;i<bb.size();i++)
	bb[i]->drawCollision();
	glPopMatrix();
	glPushMatrix();
		for(int i=0;i<1;i++)
	part[i].renderParticles();
	glPopMatrix();
	glPushMatrix();
	glTranslated(0,0,-5.5);
	glRotated(door[0]->getRotPorte(),0,0.5,0);
	door[0]->draw();
	glPopMatrix();
	
	glPushMatrix();
	glTranslated(0,0,5.5);
	glRotated(door[1]->getRotPorte(),0,0.5,0);
	door[1]->draw();
	glPopMatrix();
	
	
		for (int i = 0; i < 4; ++i) {
      
        float wheelX = (i % 2 == 0 ? 7.5f : -15.5f);
        float wheelZ = (i < 2 ? 7.5f : -10.5f);
        float wheelY = -5.25f - suspensionHeight[i];

        glPushMatrix();
        glTranslatef(wheelX, wheelY, wheelZ);
        glScaled(WHEEL_RADIUS,WHEEL_RADIUS,WHEEL_RADIUS);
        wheel[i]->draw();
	glPopMatrix();
	}
	
	glPushMatrix();
	glTranslated(0,0,0);
	v->draw();
	vv->draw();
	tab->draw();
	glPopMatrix();
}


void vehicule::elementOtherCars()
{
		for (int i = 0; i < 4; ++i) {
      
        
        float wheelX = (i % 2 == 0 ? 33.5f : -28.5f);
        float wheelZ = (i < 2 ? 18.5f : -20.5f);
        float wheelY = -9.25f - suspensionHeight[i];

        glPushMatrix();
        glTranslatef(wheelX, wheelY, wheelZ);
        glScaled(WHEEL_RADIUS2,WHEEL_RADIUS2,WHEEL_RADIUS2);
        wheel[i]->draw();
	glPopMatrix();
	}
}




void vehicule::handleKeyPress(unsigned int key, int x, int y) {
	switch(key)
	{
	 case GLUT_KEY_UP:  // Move car left
	     up=true;    
            break;
            
        case GLUT_KEY_DOWN:  // Move car right
        down=true;
            break;
            
       
             case GLUT_KEY_RIGHT:  // Turn car left
             right=true;
            break;
            
        case GLUT_KEY_LEFT:  // Turn car right
        left=true;
            break;
        }
}

void vehicule::keyboard(unsigned char key, int x, int y)
{
	switch(key)
	{
		case 32:
			space=true;
	
  
			break;
		case 'a':
			if(speed<0.01f)
			{
			
		     modeAvancer=true;
		     modeReculer=false;
		 }
		     break;
		case 'd':
				if(speed<0.01f)
			{
			
			modeReculer=true;
			 modeAvancer=false;
		}
			break;
	}
}

void vehicule::keyboardUP(unsigned char key, int x, int y)
{
	switch(key)
	{
		case 32:
			space=false;
			break;
			
	}
}

void vehicule::handleKeyPressUP(unsigned int key, int x, int y) {
	switch(key)
	{
		case GLUT_KEY_UP:  // Move car left
	     up=false;
	     break;
	     case GLUT_KEY_DOWN:  // Move car right
        down=false;
        break;
	     case GLUT_KEY_RIGHT:  // Turn car left
             right=false;
             break;
                case GLUT_KEY_LEFT:  // Turn car right
        		left=false;
        		break;
        		
        	
             
	     
	}
}
