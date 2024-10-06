#include"camera.h"

camera::camera()
{
	camPitch=0.0f;
	camYaw=0.0f;
	mousevel=0.2f;
	movevel=1.5f;
	mi=false;
	mi2=false;
	MidX=480;
	MidY=270;
	sensitivity = 0.005f;
	followDistance = 15.0f;
	cameraHeight = 3.0f;

}
camera::~camera()
{
	
}
void camera::moveCamera(float dir)
{
	float rad=(camYaw+dir)*M_PI/180.0;

	loc.x-=sin(rad)*movevel;
	loc.z-=cos(rad)*movevel;


}
void camera::lockCamera()
{
	    if (camPitch > 1.25f) camPitch = 1.25f;
    if (camPitch < -0.25f) camPitch = -0.25f;
	
	
		if(camYaw<0.0)
		camYaw+=360.0;
	if(camYaw>360.0)
		camYaw-=360;


	
	
}


void camera::moveCameraUp(float dir)
{
    float rad=(camPitch+dir)*M_PI/180.0;
    loc.y-=sin(rad)*movevel;    
}

void camera::control(int x,int y)
{


		
if(mi)
{
	float deltaX = sensitivity;

    camYaw += (MidX-x)*deltaX;
    glutWarpPointer(MidX,MidY);
    glutSetCursor(GLUT_CURSOR_CROSSHAIR);
	lockCamera();
}
else if(mi2)
{
    float deltaY =  sensitivity;

    camPitch +=  (MidY-y)*deltaY;
    glutWarpPointer(MidX,MidY);
    glutSetCursor(GLUT_CURSOR_CROSSHAIR);
	lockCamera();
}
else
{
	glutSetCursor(GLUT_CURSOR_NONE);
}

}


void camera::update(vector3d objectPosition)
{
 	float offsetX = followDistance * cos(camPitch) * sin(camYaw);
    float offsetY = followDistance * sin(camPitch);
    float offsetZ = followDistance * cos(camPitch) * cos(camYaw);

    // Set the camera's position relative to the car
    
	vector3d cameraPosition = objectPosition + vector3d(offsetX, offsetY + cameraHeight, offsetZ);

    // Camera target (car position)
    vector3d cameraTarget = objectPosition;

    // Up vector (Y is up)
    vector3d upVector = vector3d(0.0f, 1.0f, 0.0f);

    // Calculate the view matrix
   gluLookAt(cameraPosition.x,cameraPosition.y,cameraPosition.z,cameraTarget.x,cameraTarget.y,cameraTarget.z,upVector.x,upVector.y,upVector.z);
}
void camera::setLocation(vector3d l)
{
	loc=l;
}
vector3d camera::getLocation()
{
	return loc;
}



void camera::mouse(int button, int state, int x, int y)
{
	if(state==GLUT_DOWN && button==GLUT_LEFT_BUTTON)
	{
	mi=true;
	}
		else if(state==GLUT_DOWN && button==GLUT_RIGHT_BUTTON)
	{
	
	      mi2=true;
	}
else
	{
		mi2=false;
		mi=false;
	
	}
	
	

	

}

void camera::setMouseVel(float speed)
{
	movevel+=speed;
	if(	movevel>2.0f)
	{
			movevel=2.0f;
	}
		if(	movevel<0.0f)
	{
			movevel=0.0f;
	}
}

	

float camera::getMouseVel()
{
	return mousevel;
}

float camera::getPitch()
{
	return camPitch;
}
float camera::getYaw()
{
	return camYaw;
}
