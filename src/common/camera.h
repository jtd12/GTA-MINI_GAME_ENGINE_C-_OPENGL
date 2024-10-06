#ifndef DEF_CAMERA_H
#define DEF_CAMERA_H
#include"vector.h"
#include <gl/gl.h>
#include<gl/glu.h>
#include<stdio.h>
#include<C:\library\freeglut\include\GL\freeglut.h>
#include"menu.hpp"

class camera
{
	public:
		camera();
		~camera();
		void control(int x,int y);
		void moveCamera(float dir);
		void moveCameraUp(float dir);
		void moveLateral(float dir,float x,float y);
		void update(vector3d objectPosition);
		void lockCamera();
		void setLocation(vector3d l);
		vector3d getLocation();
		void mouse(int button, int state, int x, int y);
		void setMouseVel(float speed);
		float getMouseVel();
		float getPitch();
		float getYaw();
		
		private:
			float camYaw;
			float camPitch;
			float mousevel;
			float movevel;
			vector3d loc;
			bool mi,mi2;
			int MidX;
			int MidY;
			float sensitivity;
			float followDistance;
			float cameraHeight;
	

};
#endif
