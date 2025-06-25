#include"robot.hpp"

robot::robot(collisionsphere ccs)
{
	angle=0.0f;
	rotation=90.0f;
	up=false;
	down=false;
	right=false;
	left=false;
	walkSpeed=0.0f;
	control=false;
	enter=false;
	exit=false;
	collision=false;
	delay=25.0f;
	fermeturePorte=false;
	 robotYVelocity = 0.0f;  // Vertical velocity (0 at rest)
	 gravity = -0.2f;        // Gravity pulling the robot down
	 jumpForce = 5.0f;      // Initial velocity when the robot jumps
	 isJumping = false;       // Is the robot currently jumping?
	 onGround = true;         // Is the robot on the ground?
	 space=false;
	 sprintSpeed=1.0f;
	 sprintKey=false;
	 cs=ccs;
	 force.change(0.0,-0.45f,0.0);
	 setPosition(vector3d(cs.center));
	 isground=false;
	 scale=vector3d(4,4,4);
	 speed=0.7f;
}

robot::~robot()
{
	
}

vector3d robot::getScale()
{
return scale;	
}

void robot::handleJump() {
    if (onGround) {
        robotYVelocity = jumpForce;  // Apply jump force
        isJumping = true;            // Set jumping state
        onGround = false;            // Robot is now in the air
    }
}


void robot::updateCollision(std::vector<collisionplane>& collplane)
{
	if(dir.y>=force.y)
			dir+=force;
			
			newPos=vector3d(getLocation());
			newPos+=dir;
		
	
			for(int i=0;i<collplane.size();i++)
				if(collision::sphereplane(newPos,collplane[i].normal,collplane[i].p[0],collplane[i].p[1],collplane[i].p[2],collplane[i].p[3],cs.r))
				{
					   onGround = true; 
				}
				
			  if (isJumping) {
        // Apply gravity to the velocity
        robotYVelocity += gravity;

        // Update the robot's position based on its velocity
        newPos.y += robotYVelocity;
    }
    
    
		
			
				 if(getLocation().y<newPos.y)
				 {
           		isground=true;
           		}
				  else
				  {
				isground=false;
				robotYVelocity = 0.0f;  // Reset the velocity
           		isJumping = false;      // Stop jumping
           		}
		
				setPosition(newPos);
}

void robot::handleCollision(vector3d robotPos,  vector3d robotDirection, float stepBackDistance) {
    robotDirection.x = -robotDirection.x;
    robotDirection.y = -robotDirection.y;
    robotDirection.z = -robotDirection.z;
    robotPos += robotDirection * stepBackDistance;
}


void robot::updateCollisionMurs(std::vector<collisionplane>& collplane,robot* rb,vehicule* voiture)
{

				
	vector3d direction=vector3d(vx,0,vz);
				


			
			
		newPos=vector3d(getLocation());
	
			for(int i=0;i<collplane.size();i++)
			{
			
				if(collision::sphereplane(newPos,collplane[i].normal,collplane[i].p[0],collplane[i].p[1],collplane[i].p[2],collplane[i].p[3],cs.r))
				{
					
				  //robotYVelocity = 0.0f;  // Apply jump force
        		  //isJumping = false;    
					   rb->cs.center.x -= vx * speed;
    				   rb->cs.center.z -= vz * speed;
					 rb->up=false;
					 rb->down=false;
					 rb->right=false;
					rb-> left=false;
					rb-> space=false;
					rb-> sprintKey=false;
					 
				 // sprintSpeed=0.002f;
			  	
					
				
				
				
				}
				else 
				{
				  if (collisionAABB(*rb, *voiture)==false)
				  {
				
				
		
					}
				}
			
		}
}

	
	void robot::setLocationInc(vector3d loc)
{
	cs.center.y+=loc.y;
}

bool robot::collisionAABB( robot& rb,  vehicule& voiture) {
    return (rb.getLocation().x < voiture.getLocation().x + voiture.getScale().x+10 &&
            rb.getLocation().x + rb.getScale().x+30 > voiture.getLocation().x &&
            rb.getLocation().z < voiture.getLocation().z + voiture.getScale().z+10 &&
            rb.getLocation().z + rb.getScale().z+10 > voiture.getLocation().z);
}

            
void robot::collisions(robot *rb,vehicule *voiture,std::vector<collisionplane>& collplane)
{
		if(getLocation().y<-1)
				{
					setLocationInc(vector3d(0,1.1f,0));
				}
				
	else
	{
		for(int i=0;i<collplane.size();i++)
			{
			
			if(collision::sphereplane(cs.center,collplane[i].normal,collplane[i].p[0],collplane[i].p[1],collplane[i].p[2],collplane[i].p[3],cs.r)==false)
			{
		
					rb->speed=1.0f;
					
					if(sprintKey){
				      sprintSpeed=2.5f;
				  }
			
			
			}
		}
		
	}
	
}

void robot::entrerVehicule(vehicule * car)
{
	
	if(mm.value==1)
	{
		enter=true;
		exit=false;
	}
	else if(mm.value==2)
	{
		exit=true;
		enter=false;
	}
	
float dist= sqrt(((getLocation().x - car->getLocation().x) * (getLocation().x - car->getLocation().x)) + ((getLocation().y - car->getLocation().y) * (getLocation().y - car->getLocation().y)) + ((getLocation().z - car->getLocation().z) * (getLocation().z - car->getLocation().z)));
	
	if(enter && dist<100)
	{
		car->setControl(true);
	
	
   }
  
	
	if(car->getControl())
	{
		delay-=0.1f;
		car->ouvrirPorte1();
		car->ouvrirPorte2();
		cs.center=car->getLocation();
		if(delay<=5)
		{
			delay=5;
			car->fermerPorte1();
			car->fermerPorte2();
			fermeturePorte=true;
		}
	}
	
	if( exit && car->getControl())
	{
		cs.center=car->getLocation()+vector3d(-50,10,0);
		car->setControl(false);
		delay=25.0f;
		
	
	}
	if(car->getControl()==false && fermeturePorte)
	{		delay-=0.1f;
			car->ouvrirPorte1();
			car->ouvrirPorte2();
			if(delay<=5)
			{
				delay=25.0f;
				car->fermerPorte1();
				car->fermerPorte2();
				fermeturePorte=false;
				
			}
	}
	
}


bool robot::getExit()
{
return exit;	
}


void robot::drawRobot(vehicule * car) {

	if(car->getControl()==false)
	{
	
	glTranslated(cs.center.x,cs.center.y,cs.center.z);
	glRotated(rotation,0,1.0,0);
	glScaled(scale.x,scale.y,scale.z);
	glColor3f(1.0f, 0.8f, 0.0f);  // Bright yellow for glow

    // Draw torso
    glPushMatrix();
    glColor3f(0.0, 0.0, 1.0);
    glScalef(1.0, 2.0, 0.5);
    glutSolidCube(1.0);
    glPopMatrix();

    // Draw head
    glPushMatrix();
    glColor3f(1.0, 1.0, 0.0);
    glTranslatef(0.0, 1.5, 0.0);
    glutSolidCube(0.6);
    glPopMatrix();

    // Draw arms
    drawArm(1.0);
    drawArm(-1.0);

    // Draw legs
    drawLeg(0.5);
    drawLeg(-0.5);
}
}

void robot::update(int value,int a) {
    angle += a; // Update the walking animation
    if (angle > 360) {
        angle -= 360;
    }
    

    
      vz = walkSpeed * sprintSpeed * cos(rotation * 3.14159 / 180.0f);
      vx = walkSpeed * sprintSpeed * sin(rotation * 3.14159 / 180.0f);
    
    cs.center.x += vx * speed;
    cs.center.z += vz * speed;
    
  
}

void robot::detectCollisionVoitures(robot* rb,vehicule* voiture)
{
	  
    	if (collisionAABB(*rb, *voiture))
	{
		 	     
				    rb->cs.center.x -= vx * speed;
    				rb->cs.center.z -= vz * speed;
    				rb-> up=false;
					rb-> down=false;
					rb-> right=false;
					rb-> left=false;
					rb-> space=false;
					rb-> sprintKey=false;
					 
		
	}
}


void robot::resetMovement(int a)
 {
 	angle=a;
 }

void robot::updateMovement(int value,bool control,blurMotion* motionBB)
{
	
		
	if(control==false)
	{


	
	if(up)
	{
		motionBB->update(1000);
		walkSpeed=2.9f;
		update(value,20.0f);
	}

	
	if(down)
	{
		walkSpeed=-2.9f;
		update(value,-20.0f);
		motionBB->update(1000);
	}
	
	
	if(right)
	{
		rotation-=10.0f;
	}
	if(left)
	{
		rotation+=10.0f;
	}
	
		if(space)
	{
		handleJump();
		update(value,10.0f);
	}
	if(sprintKey){
			motionBB->update(2000);
		sprintSpeed=2.5f;
	}
	
	if(sprintKey==false)
	{
		sprintSpeed=1.0f;
	}	
	
	
	if(up==false && down==false && space==false)
	{
		resetMovement(0.0f);
		motionBB->update(-800);
	}
	
}
	

	
}
    
void robot::drawArm(float side) {
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(side, 0.5, 0.0);
    glRotatef(side * 30.0f * sin(angle * 3.14159 / 180), 1.0, 0.0, 0.0);
    glTranslatef(0.0, -0.5, 0.0);
    glScalef(0.2, 1.0, 0.2);
    glutSolidCube(1.0);
    glPopMatrix();
}

void robot::drawLeg(float side) {
    glPushMatrix();
    glColor3f(0.0, 1.0, 0.0);
    glTranslatef(side, -1.0, 0.0);
    glRotatef(side * 30.0f * sin(angle * 3.14159 / 180), 1.0, 0.0, 0.0);
    glTranslatef(0.0, -0.5, 0.0);
    glScalef(0.2, 1.0, 0.2);
    glutSolidCube(1.0);
    glPopMatrix();
}

  vector3d robot::getLocation()
  {
  	return cs.center;
  }
  
  void robot::setLocation(vector3d location)
{
	cs.center.change(location);
}

  void robot::setPosition(vector3d pos)
   {
  cs.center=pos;
  setLocation(pos);
   }
  

void robot::handleKeyPress(unsigned int key, int x, int y) {
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



void robot::handleKeyPressUP(unsigned int key, int x, int y) {
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

void robot::keyboard(unsigned char key, int x, int y)
{
	switch(key)
	{
		case 'c':
	
			break;
		case 'v':

			break;
		case 32:
			space=true;
			break;
		case 'z':
			sprintKey=true;
			break;
		
	}
}

void robot::keyboardUP(unsigned char key, int x, int y)
{
	switch(key)
	{
		case 'c':
		
			break;
		case 'v':
	
			break;
		case 32:
			space=false;
			break;
		case 'z':
			sprintKey=false;
			break;
	}
}



